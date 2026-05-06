% 电流采样：Σδ采样 
% 分压电阻：33K/2.2K

drive.V_bus = 36;               % 母线电压

% 逆变器参数
drive.f_TIM = 200e6;            % 定时器频率 用来计算PWM控制精度
drive.CNT_PWM = 10000;
drive.f_PWM = drive.f_TIM/drive.CNT_PWM;     
drive.T_PWM = 1/drive.f_PWM;  
drive.Rs_bus = 0;               % 电源输出电阻
drive.I_max = 15;               % 最大线电流
drive.V_min = 12;               % 最小母线电压
drive.V_max = 48;               % 最大母线电压

drive.dead_time = 0e-9;         %死区时间     
drive.R_bus = 0.1;
% ADC参数
drive.ADC_Vref             = 3.326;					    % ADC voltage reference for LAUNCHXL-F28379D
drive.ADC_MaxCount         = 2^14-1;					% Max count for 12 bit ADC
drive.I_gain = 0.123/2;                                   % 电流传感器增益 单位:V/A
drive.I_noise = [0.0005, 0.0005, 0.0005]*1;                % 电流采样噪声标准差
drive.I_offset = drive.ADC_Vref/2+randn(3,1)*0.001*0;   % ADC转换偏置           
drive.V_gain = 2.2/(33+2.2);

