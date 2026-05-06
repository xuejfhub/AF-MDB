% 电流采样：线性霍尔传感器：CC6903SO-10A
% 分压电阻：20K/2.2K

% 逆变器参数
drive.V_bus = 24;               % 母线电压
drive.Rs_bus = 0;               % 电源输出电阻
drive.f_TIM = 200e6;            % 定时器频率 用来计算PWM控制精度
drive.CNT_PWM = 10000;
drive.f_PWM = drive.f_TIM/drive.CNT_PWM;     
drive.T_PWM = 1/drive.f_PWM;  
% ADC参数
drive.ADC_Vref             = 3.3;					    % ADC voltage reference for LAUNCHXL-F28379D
drive.ADC_MaxCount         = 2^12-2;					% Max count for 12 bit ADC
drive.I_gain = 0.132*2;                                   % 电流传感器增益 单位:V/A
drive.I_noise = [0.001, 0.001, 0.001]*1;                % 电流采样噪声标准差
drive.I_offset = drive.ADC_Vref/2+randn(3,1)*0.001*1;   % ADC转换偏置           
drive.V_gain = 2.2/(20+2.2);
 