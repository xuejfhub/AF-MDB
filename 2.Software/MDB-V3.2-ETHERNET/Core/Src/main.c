/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "lwip.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <math.h>          // sin/cos 函数
#include "lwip/netif.h"
#include "lwip/stats.h"
#include "lwip/udp.h"      // UDP API
#include "lwip/pbuf.h"     // pbuf 管理
#include "lwip/ip4_addr.h" // IP 地址操作

// 重定向需要的头文件
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// ADC 数据缓冲区（DMA 循环模式,存储两次采样）
uint32_t adc1[8];  // ADC1 数据缓冲区（4 个通道 × 2 次采样 = 8）
uint32_t adc2[8];  // ADC2 数据缓冲区（4 个通道 × 2 次采样 = 8）

// SPWM 发生器变量
float spwm_angle = 0.0f;           // SPWM 相位角度 (0-360°)
const float spwm_freq = 50.0f;     // SPWM 频率 50Hz
float spwm_duty_min = 0.2f;        // 最小占空比 20%
float spwm_duty_max = 0.8f;        // 最大占空比 80%

// UDP 目标地址（动态获取）
ip_addr_t remote_ip;               // 远程 IP 地址
uint16_t remote_port = 0;          // 远程端口号
uint8_t remote_addr_valid = 0;     // 远程地址有效标志

// UDP 发送缓冲区（1KB）
#define UDP_BUFFER_SIZE 1024
uint8_t udp_tx_buffer[UDP_BUFFER_SIZE];
uint16_t udp_buffer_index = 0;     // 当前缓冲区写入位置
uint32_t last_send_tick = 0;       // 上次发送时间戳（单位: TIM1 中断次数）
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// 外部变量声明
extern ETH_HandleTypeDef heth;
extern struct netif gnetif;

// 串口重定向printf - 支持多种编译器
#ifdef __GNUC__
int __io_putchar(int ch)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}

// 为GCC添加_write函数支持
int _write(int file, char *ptr, int len)
{
  int DataIdx;
  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    __io_putchar(*ptr++);
  }
  return len;
}
#else
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}
#endif

//=============================================================================
// LAN9303 交换机寄存器诊断
//=============================================================================

/* LAN9303 虚拟交换寄存器读取 (通过 MDIO Clause 22) */
uint32_t LAN9303_Read_VirtualReg(uint16_t reg_addr)
{
  uint32_t reg_low, reg_high;
  
  // 写入要访问的虚拟寄存器地址到 VIRT_PHY_ADDR (0x10)
  HAL_ETH_WritePHYRegister(&heth, 0, 0x10, reg_addr);
  
  // 从 VIRT_PHY_DATA_LOW (0x11) 和 VIRT_PHY_DATA_HIGH (0x12) 读取32位数据
  HAL_ETH_ReadPHYRegister(&heth, 0, 0x11, &reg_low);
  HAL_ETH_ReadPHYRegister(&heth, 0, 0x12, &reg_high);
  
  return (reg_high << 16) | reg_low;
}

/* 检查 LAN9303 交换机状态 */
void Check_LAN9303_Switch(void)
{
  printf("\r\n========== LAN9303 交换机寄存器诊断 ==========\r\n");
  
  // 1. 读取芯片 ID
  uint32_t chip_id = LAN9303_Read_VirtualReg(0x50);
  printf("Chip ID: 0x%08lX (应为 0x00009303)\r\n", chip_id);
  
  // 2. 读取 Switch 配置
  uint32_t sw_cfg = LAN9303_Read_VirtualReg(0x0400);
  printf("Switch Config (0x0400): 0x%08lX\r\n", sw_cfg);
  printf("  - Switch Enable: %s\r\n", (sw_cfg & (1<<7)) ? "✅ 启用" : "❌ 禁用");
  
  // 3. 读取 Port 0 (CPU Port) 配置
  uint32_t port0_cfg = LAN9303_Read_VirtualReg(0x0410);
  printf("Port 0 (CPU) Config (0x0410): 0x%08lX\r\n", port0_cfg);
  printf("  - RX Enable: %s\r\n", (port0_cfg & (1<<2)) ? "✅" : "❌");
  printf("  - TX Enable: %s\r\n", (port0_cfg & (1<<1)) ? "✅" : "❌");
  
  // 4. 读取 Port 1 配置
  uint32_t port1_cfg = LAN9303_Read_VirtualReg(0x0420);
  printf("Port 1 Config (0x0420): 0x%08lX\r\n", port1_cfg);
  printf("  - RX Enable: %s\r\n", (port1_cfg & (1<<2)) ? "✅" : "❌");
  printf("  - TX Enable: %s\r\n", (port1_cfg & (1<<1)) ? "✅" : "❌");
  
  // 5. 读取 Port 2 配置
  uint32_t port2_cfg = LAN9303_Read_VirtualReg(0x0430);
  printf("Port 2 Config (0x0430): 0x%08lX\r\n", port2_cfg);
  printf("  - RX Enable: %s\r\n", (port2_cfg & (1<<2)) ? "✅" : "❌");
  printf("  - TX Enable: %s\r\n", (port2_cfg & (1<<1)) ? "✅" : "❌");
  
  // 6. 读取 VLAN 配置
  uint32_t vlan_port0 = LAN9303_Read_VirtualReg(0x0440);
  uint32_t vlan_port1 = LAN9303_Read_VirtualReg(0x0444);
  uint32_t vlan_port2 = LAN9303_Read_VirtualReg(0x0448);
  printf("VLAN Port Members:\r\n");
  printf("  Port 0: 0x%08lX (Bits: ", vlan_port0);
  if (vlan_port0 & (1<<0)) printf("P0 ");
  if (vlan_port0 & (1<<1)) printf("P1 ");
  if (vlan_port0 & (1<<2)) printf("P2");
  printf(")\r\n");
  printf("  Port 1: 0x%08lX (Bits: ", vlan_port1);
  if (vlan_port1 & (1<<0)) printf("P0 ");
  if (vlan_port1 & (1<<1)) printf("P1 ");
  if (vlan_port1 & (1<<2)) printf("P2");
  printf(")\r\n");
  printf("  Port 2: 0x%08lX (Bits: ", vlan_port2);
  if (vlan_port2 & (1<<0)) printf("P0 ");
  if (vlan_port2 & (1<<1)) printf("P1 ");
  if (vlan_port2 & (1<<2)) printf("P2");
  printf(")\r\n");
  
  // 检查关键问题：Port 0 能否向 Port 1/2 转发
  if (!(vlan_port0 & ((1<<1) | (1<<2)))) {
    printf("\r\n⚠️⚠️⚠️ 警告：Port 0 (CPU) 无法转发到 Port 1/2！\r\n");
    printf("这会导致 STM32 发送的数据无法到达外部网络。\r\n");
  } else {
    printf("\r\n✅ Port 0 可以转发到外部端口。\r\n");
  }
  
  printf("============================================\r\n");
}

//=============================================================================
// 以太网基本状态显示（精简版）
//=============================================================================

/* 显示网络基本信息 */
void Show_Network_Info(void)
{
  printf("\r\n========== 网络状态 ==========\r\n");
  printf("  IP: %s\r\n", ip4addr_ntoa(netif_ip4_addr(&gnetif)));
  printf("  Netmask: %s\r\n", ip4addr_ntoa(netif_ip4_netmask(&gnetif)));
  printf("  Gateway: %s\r\n", ip4addr_ntoa(netif_ip4_gw(&gnetif)));
  printf("  MAC: %02X:%02X:%02X:%02X:%02X:%02X\r\n",
         gnetif.hwaddr[0], gnetif.hwaddr[1], gnetif.hwaddr[2],
         gnetif.hwaddr[3], gnetif.hwaddr[4], gnetif.hwaddr[5]);
  printf("  Link: %s\r\n", netif_is_link_up(&gnetif) ? "UP" : "DOWN");
  printf("  Netif: %s\r\n", netif_is_up(&gnetif) ? "UP" : "DOWN");
  printf("  连接模式: 直连（无路由器）\r\n");
  printf("==============================\r\n");
}

//=============================================================================
// UDP Echo Server（UDP 回显服务器）
//=============================================================================

static struct udp_pcb *udp_echo_pcb = NULL;

/* UDP 接收回调函数（接收 PC 数据包，记录远程地址）*/
void udp_echo_recv_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p,
                           const ip_addr_t *addr, u16_t port)
{
  if (p != NULL)
  {
    // 记录远程 IP 和端口（首次接收或更新）
    ip_addr_copy(remote_ip, *addr);
    remote_port = port;
    remote_addr_valid = 1;
    
    // 释放接收的数据包（不需要回显）
    pbuf_free(p);
  }
}

/* 初始化 UDP Echo Server */
void UDP_Echo_Server_Init(uint16_t port)
{
  err_t err;
  
  // 创建 UDP PCB（使用 IP_PROTO_UDP）
  udp_echo_pcb = udp_new_ip_type(IPADDR_TYPE_V4);
  
  if (udp_echo_pcb != NULL)
  {
    // 绑定到本地 IP 和指定端口（明确绑定到 gnetif 的 IP）
    err = udp_bind(udp_echo_pcb, netif_ip4_addr(&gnetif), port);
    
    if (err == ERR_OK)
    {
      // 设置接收回调函数
      udp_recv(udp_echo_pcb, udp_echo_recv_callback, NULL);
      printf("[UDP] Echo Server 已启动，监听端口 %d\r\n", port);
    }
    else
    {
      printf("[UDP] ❌ 绑定端口失败\r\n");
      udp_remove(udp_echo_pcb);
      udp_echo_pcb = NULL;
    }
  }
  else
  {
    printf("[UDP] ❌ 创建 PCB 失败\r\n");
  }
}

//=============================================================================
// 以太网状态显示（精简版 - 仅保留基本信息）
//=============================================================================

/* 显示 lwIP 统计信息（精简版）*/
void Show_lwIP_Stats(void)
{
  printf("\r\n[lwIP Stats]\r\n");
  
#if LWIP_STATS
  printf("  Link: RX=%u TX=%u | ", lwip_stats.link.recv, lwip_stats.link.xmit);
  printf("IP: RX=%u TX=%u | ", lwip_stats.ip.recv, lwip_stats.ip.xmit);
  printf("ICMP: RX=%u TX=%u | ", lwip_stats.icmp.recv, lwip_stats.icmp.xmit);
  printf("UDP: RX=%u TX=%u\r\n", lwip_stats.udp.recv, lwip_stats.udp.xmit);
#else
  printf("  Statistics disabled\r\n");
#endif
}

/* 旧的详细诊断函数 - 保留用于故障排查 */
void _OLD_Test_MDIO_ReadWrite(void)
{
  printf("\r\n========== MDIO 读写测试 ==========\r\n");
  printf("  LAN9303 PHY 地址映射:\r\n");
  printf("    PHY0 = 虚拟 CPU 端口 (STM32 连接)\r\n");
  printf("    PHY1 = Port1 外部端口\r\n");
  printf("    PHY2 = Port2 外部端口\r\n\r\n");
  
  // 扫描 PHY 地址 0-2
  for(uint32_t phy_addr = 0; phy_addr <= 2; phy_addr++)
  {
    uint32_t id1 = 0, id2 = 0, bmsr = 0, bmcr = 0;
    
    if(HAL_ETH_ReadPHYRegister(&heth, phy_addr, 2, &id1) == HAL_OK &&
       HAL_ETH_ReadPHYRegister(&heth, phy_addr, 3, &id2) == HAL_OK)
    {
      HAL_ETH_ReadPHYRegister(&heth, phy_addr, 0, &bmcr);
      HAL_ETH_ReadPHYRegister(&heth, phy_addr, 1, &bmsr);
      
      printf("  PHY[%lu]: ID1=0x%04lX ID2=0x%04lX BMCR=0x%04lX BMSR=0x%04lX\r\n",
             phy_addr, id1 & 0xFFFF, id2 & 0xFFFF, bmcr & 0xFFFF, bmsr & 0xFFFF);
      printf("         Link=%s, Speed=%s, Duplex=%s\r\n",
             (bmsr & (1<<2)) ? "UP" : "DOWN",
             (bmcr & (1<<13)) ? "100M" : "10M",
             (bmcr & (1<<8)) ? "Full" : "Half");
    }
  }
  
  // MDIO 写入测试 (测试 PHY0 的 BMCR 寄存器部分位)
  uint32_t original_bmcr = 0, modified_bmcr = 0;
  printf("\r\n  MDIO 写入测试 (PHY0):\r\n");
  
  // 读取原始 BMCR
  HAL_ETH_ReadPHYRegister(&heth, 0, 0, &original_bmcr);
  printf("    原始 BMCR = 0x%04lX\r\n", original_bmcr & 0xFFFF);
  
  // 测试写入 (切换 Loopback bit 15, 不影响通信)
  uint32_t test_val = original_bmcr ^ (1<<15);  // 翻转 Loopback 位
  HAL_ETH_WritePHYRegister(&heth, 0, 0, test_val);
  HAL_Delay(10);
  HAL_ETH_ReadPHYRegister(&heth, 0, 0, &modified_bmcr);
  printf("    写入后   = 0x%04lX\r\n", modified_bmcr & 0xFFFF);
  
  // 恢复原始值
  HAL_ETH_WritePHYRegister(&heth, 0, 0, original_bmcr);
  HAL_Delay(10);
  
  printf("    结果: %s\r\n", 
         (modified_bmcr == test_val) ? "✅ MDIO 读写正常" : "⚠️ 写入部分成功");
  
  printf("==========================================\r\n");
}

/* 2. ETH 寄存器状态检查 */
void Check_ETH_Registers(void)
{
  printf("\r\n========== ETH 寄存器状态 ==========\r\n");
  
  // MAC 配置寄存器
  uint32_t maccr = heth.Instance->MACCR;
  printf("  MACCR   = 0x%08lX\r\n", maccr);
  printf("    Speed=%s, Duplex=%s, Loopback=%s\r\n",
         (maccr & ETH_MACCR_FES) ? "100M" : "10M",
         (maccr & ETH_MACCR_DM) ? "Full" : "Half",
         (maccr & ETH_MACCR_LM) ? "ON" : "OFF");
  
  // DMA 状态寄存器
  printf("  DMACSR  = 0x%08lX\r\n", heth.Instance->DMACSR);
  printf("  DMADSR  = 0x%08lX ", heth.Instance->DMADSR);
  uint32_t dmadsr = heth.Instance->DMADSR;
  printf("(TxState=%lu, RxState=%lu)\r\n", 
         (dmadsr >> 12) & 0xF, (dmadsr >> 8) & 0xF);
  
  // DMA 中断状态
  printf("  DMAISR  = 0x%08lX\r\n", heth.Instance->DMAISR);
  
  // 描述符地址
  printf("  Tx Desc = 0x%08lX\r\n", (uint32_t)heth.Instance->DMACTDLAR);
  printf("  Rx Desc = 0x%08lX\r\n", (uint32_t)heth.Instance->DMACRDLAR);
  
  printf("==========================================\r\n");
}

/* 3. lwIP 网络接口状态 */
void Check_lwIP_Netif(void)
{
  printf("\r\n========== lwIP Netif 状态 ==========\r\n");
  
  // netif 基本状态
  printf("  netif.flags   = 0x%02X\r\n", gnetif.flags);
  printf("    UP=%d, Link=%d, Broadcast=%d\r\n",
         !!(gnetif.flags & NETIF_FLAG_UP),
         !!(gnetif.flags & NETIF_FLAG_LINK_UP),
         !!(gnetif.flags & NETIF_FLAG_BROADCAST));
  
  // IP 配置
  printf("  IP Address    = %u.%u.%u.%u\r\n",
         ip4_addr1(&gnetif.ip_addr), ip4_addr2(&gnetif.ip_addr),
         ip4_addr3(&gnetif.ip_addr), ip4_addr4(&gnetif.ip_addr));
  printf("  Netmask       = %u.%u.%u.%u\r\n",
         ip4_addr1(&gnetif.netmask), ip4_addr2(&gnetif.netmask),
         ip4_addr3(&gnetif.netmask), ip4_addr4(&gnetif.netmask));
  printf("  Gateway       = %u.%u.%u.%u\r\n",
         ip4_addr1(&gnetif.gw), ip4_addr2(&gnetif.gw),
         ip4_addr3(&gnetif.gw), ip4_addr4(&gnetif.gw));
  
  // MAC 地址
  printf("  MAC Address   = %02X:%02X:%02X:%02X:%02X:%02X\r\n",
         gnetif.hwaddr[0], gnetif.hwaddr[1], gnetif.hwaddr[2],
         gnetif.hwaddr[3], gnetif.hwaddr[4], gnetif.hwaddr[5]);
  
  printf("==========================================\r\n");
}

/* 4. lwIP 协议栈统计 */
void Check_lwIP_Stats(void)
{
  printf("\r\n========== lwIP 统计信息 ==========\r\n");
  
#if LWIP_STATS
  printf("  [Link] RX=%u TX=%u Drop=%u Err=%u\r\n",
         lwip_stats.link.recv, lwip_stats.link.xmit,
         lwip_stats.link.drop, lwip_stats.link.err);
  
  printf("  [IP4]  RX=%u TX=%u Drop=%u Err=%u\r\n",
         lwip_stats.ip.recv, lwip_stats.ip.xmit,
         lwip_stats.ip.drop, lwip_stats.ip.err);
  
  printf("  [ICMP] RX=%u TX=%u Drop=%u Err=%u\r\n",
         lwip_stats.icmp.recv, lwip_stats.icmp.xmit,
         lwip_stats.icmp.drop, lwip_stats.icmp.err);
  
  printf("  [UDP]  RX=%u TX=%u Drop=%u\r\n",
         lwip_stats.udp.recv, lwip_stats.udp.xmit, lwip_stats.udp.drop);
#else
  printf("  ⚠️ LWIP_STATS 未启用，无详细统计\r\n");
#endif
  
  printf("==========================================\r\n");
}

/* 5. RMII 数据收发测试 */
void Check_RMII_Activity(void)
{
  printf("\r\n========== RMII 数据活动检测 ==========\r\n");
  
  // 读取 DMA 计数器（如果硬件支持）
  // 注意：STM32H7 的 ETH 没有直接的包计数寄存器，需要通过 DMA 状态判断
  
  uint32_t dmadsr = heth.Instance->DMADSR;
  uint32_t tx_state = (dmadsr >> 12) & 0xF;
  uint32_t rx_state = (dmadsr >> 8) & 0xF;
  
  printf("  DMA Tx State: ");
  switch(tx_state) {
    case 0: printf("Stopped\r\n"); break;
    case 1: printf("Fetching Desc\r\n"); break;
    case 2: printf("Waiting for Status\r\n"); break;
    case 3: printf("Reading Data\r\n"); break;
    case 6: printf("Suspended\r\n"); break;
    case 7: printf("Closing Desc\r\n"); break;
    default: printf("Unknown (%lu)\r\n", tx_state); break;
  }
  
  printf("  DMA Rx State: ");
  switch(rx_state) {
    case 0: printf("Stopped\r\n"); break;
    case 1: printf("Fetching Desc\r\n"); break;
    case 3: printf("Waiting for Packet\r\n"); break;
    case 5: printf("Closing Desc\r\n"); break;
    case 7: printf("Transferring Data\r\n"); break;
    default: printf("Unknown (%lu)\r\n", rx_state); break;
  }
  
  // 检查是否有错误标志
  uint32_t dmaisr = heth.Instance->DMAISR;
  if(dmaisr & 0xFFFF) {
    printf("  ⚠️ DMA 中断标志: 0x%04lX\r\n", dmaisr & 0xFFFF);
  } else {
    printf("  ✅ 无 DMA 错误\r\n");
  }
  
  printf("==========================================\r\n");
}

/* 6. 主动发送 ARP 测试 TX 功能 */
void Test_ARP_Request(void)
{
  printf("\r\n========== ARP 请求测试 ==========\r\n");
  
  // 目标 IP: 192.168.1.1 (网关)
  ip4_addr_t target_ip;
  IP4_ADDR(&target_ip, 192, 168, 1, 1);
  
  printf("  发送 ARP 请求到 192.168.1.1...\r\n");
  
  // 发送 ARP 请求
  err_t result = etharp_request(&gnetif, &target_ip);
  
  if (result == ERR_OK) {
    printf("  ✅ ARP 请求已发送\r\n");
  } else {
    printf("  ❌ ARP 请求发送失败 (err=%d)\r\n", result);
  }
  
  printf("==========================================\r\n");
}

/* 完整诊断入口 */
void Run_Full_Diagnostics(void)
{
  printf("\r\n\r\n");
  printf("##################################################\r\n");
  printf("#         以太网完整诊断 - %lu ms           #\r\n", HAL_GetTick());
  printf("##################################################\r\n");
  
  Check_DMA_Descriptors();  // 首先检查 DMA 描述符
  Test_MDIO_ReadWrite();
  Check_ETH_Registers();
  Check_lwIP_Netif();
  Check_lwIP_Stats();
  Check_RMII_Activity();
  Test_ARP_Request();  // 测试 TX 发送
  
  printf("\r\n");
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */
  __HAL_RCC_D2SRAM1_CLK_ENABLE();  // 使能 D2 SRAM1 时钟，用于 LWIP 内存
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM15_Init();
  MX_USART1_UART_Init();
  MX_ADC2_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
//  MX_LWIP_Init();
  /* USER CODE BEGIN 2 */
  
  /* ========== 外设启动初始化 ========== */
  
  /* GPIO 初始化延时 */
  HAL_Delay(100);
  
  /* UART 接收超时配置（可选，用于接收不定长数据） */
  HAL_UART_EnableReceiverTimeout(&huart1);
  HAL_UART_ReceiverTimeout_Config(&huart1, 0xFF);
  
  /* ADC 校准（建议在启动 DMA 之前执行） */
  HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
  HAL_ADCEx_Calibration_Start(&hadc2, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
  
  /* 启动 ADC DMA 循环采集（每个通道采样 2 次，共 8 个数据） */
  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc1, 8);  // ADC1: 4 个通道 × 2 次 = 8
  HAL_ADC_Start_DMA(&hadc2, (uint32_t *)adc2, 8);  // ADC2: 4 个通道 × 2 次 = 8

  /* 启动 TIM3 编码器模式 */
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
  
  /* 启动 TIM3 通道 3 输入捕获中断 */
  HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);
  
  /* 启动 TIM1 PWM 输出（3 个通道） */
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  
  /* 启动 TIM1 互补输出（3 个通道） */
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
  
  /* 启动 TIM1 基础定时器中断 */
  HAL_TIM_Base_Start_IT(&htim1);
  
  /* ========== 以太网模块初始化 ========== */
  
  printf("\r\n========== 以太网初始化 ==========%s\r\n", "");
  
  /* 启动 TIM15 PWM 输出（为 LAN9303 提供 25MHz 时钟） */
  HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);
  HAL_Delay(100);


  /* 初始化 LWIP (包含以太网 HAL 初始化) */
  MX_LWIP_Init();
  
  SCB_CleanInvalidateDCache();
  /* 复位LAN9303并等待 */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
  HAL_Delay(10);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
  HAL_Delay(100);
  printf("\r\n========== 初始化完成 ==========\r\n");
  
  /* 等待链路稳定 */
  HAL_Delay(500);
  
  /* 显示网络信息 */
  Show_Network_Info();
  
  /* 检查 LAN9303 交换机寄存器 */
  HAL_Delay(500); // 等待交换机稳定
  Check_LAN9303_Switch();
  
  /* 启动 UDP Echo Server (端口 7) */
  UDP_Echo_Server_Init(7);
  
  printf("\r\n系统就绪，等待 UDP 数据...\r\n\r\n");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  
  while (1)
  {
    /* 处理 lwIP 协议栈（高速模式：无延迟，无打印）*/
    MX_LWIP_Process();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    
    /* 高速 UDP 优化：
     * - 移除所有周期性打印（避免串口阻塞）
     * - 移除 HAL_Delay(1)（避免不必要的延迟）
     * - 主循环专注于 lwIP 处理，最大化吞吐量
     */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  RCC_OscInitStruct.PLL.PLLR = 4;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CKPER;
  PeriphClkInitStruct.CkperClockSelection = RCC_CLKPSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

//=============================================================================
// TIM1 更新中断回调函数 - 10kHz 中断频率
// - 生成三相 50Hz SPWM 波形（相位差 120°）
// - 采集 ADC 数据并通过 UDP 发送
//=============================================================================

// 数学常量
#define PI 3.14159265358979323846f
#define DEG_TO_RAD (PI / 180.0f)

// TIM1 参数（中心对齐模式：向上和向下都触发中断）
#define TIM1_PERIOD 9999                    // TIM1 ARR 值
#define TIM1_FREQ 20000.0f                  // TIM1 中断频率 20kHz（中心对齐模式 = 200MHz / 10000）
#define SPWM_FREQ 50.0f                     // SPWM 输出频率 50Hz
#define ANGLE_INCREMENT (360.0f * SPWM_FREQ / TIM1_FREQ)  // 每次中断角度增量 = 0.9°

// UDP 发送控制（1ms 或缓冲区满时发送）
#define UDP_SEND_TIMEOUT 20                 // 超时时间 20 次中断 = 1ms（20kHz → 0.05ms/次）
static uint16_t adc_sample_counter = 0;     // ADC 采样计数器（每 20 次中断采样一次）

// ADC 数据结构（用于 UDP 发送）
typedef struct {
  uint16_t adc1_ch[4];  // ADC1 的 4 个通道平均值
  uint16_t adc2_ch[4];  // ADC2 的 4 个通道平均值
} ADC_Data_t;

/* UDP 发送函数（缓冲区满或超时时调用）*/
void UDP_Send_Buffer(void)
{
  if (!remote_addr_valid || udp_buffer_index == 0) {
    return;  // 无有效地址或缓冲区为空，不发送
  }
  
  // 如果数据不足 1KB，用 0 补齐
  if (udp_buffer_index < UDP_BUFFER_SIZE) {
    memset(&udp_tx_buffer[udp_buffer_index], 0, UDP_BUFFER_SIZE - udp_buffer_index);
  }
  
  // 通过 UDP 发送整个缓冲区（1KB）
  struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, UDP_BUFFER_SIZE, PBUF_RAM);
  if (p != NULL)
  {
    memcpy(p->payload, udp_tx_buffer, UDP_BUFFER_SIZE);
    udp_sendto(udp_echo_pcb, p, &remote_ip, remote_port);
    pbuf_free(p);
  }
  
  // 重置缓冲区
  udp_buffer_index = 0;
  last_send_tick = 0;
}

/* TIM1 更新中断回调函数（20kHz 中断频率）*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM1)
  {
    // ========== 1. 生成三相 SPWM 波形（每次中断更新）==========
    
    // 更新相位角度（0-360°）
    spwm_angle += ANGLE_INCREMENT;
    if (spwm_angle >= 360.0f) {
      spwm_angle -= 360.0f;
    }
    
    // 计算三相正弦波（相位差 120°）
    float sin_a = sinf(spwm_angle * DEG_TO_RAD);                      // A 相: 0°
    float sin_b = sinf((spwm_angle - 120.0f) * DEG_TO_RAD);           // B 相: -120°
    float sin_c = sinf((spwm_angle + 120.0f) * DEG_TO_RAD);           // C 相: +120°
    
    // 转换为占空比（20%-80%）
    // sin 范围 [-1, 1] → 映射到 [0.2, 0.8]
    float duty_a = spwm_duty_min + (sin_a + 1.0f) * 0.5f * (spwm_duty_max - spwm_duty_min);
    float duty_b = spwm_duty_min + (sin_b + 1.0f) * 0.5f * (spwm_duty_max - spwm_duty_min);
    float duty_c = spwm_duty_min + (sin_c + 1.0f) * 0.5f * (spwm_duty_max - spwm_duty_min);
    
    // 更新 PWM 占空比（TIM1 CH1/CH2/CH3）
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (uint32_t)(duty_a * TIM1_PERIOD));
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, (uint32_t)(duty_b * TIM1_PERIOD));
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (uint32_t)(duty_c * TIM1_PERIOD));
    
    
    // ========== 2. 采集 ADC 数据并写入缓冲区（每 20 次中断 = 1ms）==========
    
    adc_sample_counter++;
    if (adc_sample_counter >= UDP_SEND_TIMEOUT)
    {
      adc_sample_counter = 0;
      last_send_tick++;  // 递增超时计数器
      
      // 检查远程地址是否有效
      if (remote_addr_valid)
      {
        // 计算 ADC 平均值（每个通道取两次采样的平均）
        ADC_Data_t adc_data;
        
        // ADC1: 通道 0-3（数组索引 0,4 | 1,5 | 2,6 | 3,7）
        adc_data.adc1_ch[0] = (uint16_t)((adc1[0] + adc1[4]) / 2);
        adc_data.adc1_ch[1] = (uint16_t)((adc1[1] + adc1[5]) / 2);
        adc_data.adc1_ch[2] = (uint16_t)((adc1[2] + adc1[6]) / 2);
        adc_data.adc1_ch[3] = (uint16_t)((adc1[3] + adc1[7]) / 2);
        
        // ADC2: 通道 0-3（数组索引 0,4 | 1,5 | 2,6 | 3,7）
        adc_data.adc2_ch[0] = (uint16_t)((adc2[0] + adc2[4]) / 2);
        adc_data.adc2_ch[1] = (uint16_t)((adc2[1] + adc2[5]) / 2);
        adc_data.adc2_ch[2] = (uint16_t)((adc2[2] + adc2[6]) / 2);
        adc_data.adc2_ch[3] = (uint16_t)((adc2[3] + adc2[7]) / 2);
        
        // 写入缓冲区（16 字节）
        if (udp_buffer_index + sizeof(ADC_Data_t) <= UDP_BUFFER_SIZE)
        {
          memcpy(&udp_tx_buffer[udp_buffer_index], &adc_data, sizeof(ADC_Data_t));
          udp_buffer_index += sizeof(ADC_Data_t);
        }
        
        // 检查发送条件：缓冲区满 或 超时 1ms
        if (udp_buffer_index >= UDP_BUFFER_SIZE || last_send_tick >= 1)
        {
          UDP_Send_Buffer();
        }
      }
    }
  }
}

/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x30000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_256B;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.BaseAddress = 0x30004000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_16KB;
  MPU_InitStruct.SubRegionDisable = 0x0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
