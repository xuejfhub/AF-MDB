%% 新建电机结构体
motor = struct();

%% 设置电机参数
% 给定参数
motor.V_rated = 36;
motor.rpm_rated = 3000;     %额定转速
motor.rpm_max = 3600;       %最高转速
motor.radps_rated = motor.rpm_rated*2*pi/60;    %额定转速
motor.radps_max = motor.rpm_max*2*pi/60;        %最高转速
motor.power_rated = 200;                        %额定功率
motor.P = 4;            %极对数
motor.Rs = 0.33/2;      %相电阻    
motor.Ls = 0.9e-3/2;    %dq轴电感
motor.Ke = 5.4*sqrt(2); %反电动势系数 V/krpm
motor.J = 18.9e-6;      %转动惯量   
motor.ENC_CNT =2500*4;  %编码器2500线双边沿采样

% 根据已知参数和电机模型，计算未知参数
motor.psi = motor.Ke/(motor.P*sqrt(3)*1000*2*pi/60);    %转子磁链
motor.Kt = 1.5*motor.psi*motor.P;                       %转矩系数
motor.T_rated = motor.power_rated/(motor.radps_rated);  %额定电流
motor.I_rated = motor.T_rated/motor.Kt;                 

motor.I_max = 16;   %驱动器最大相电流
motor.T_max = motor.I_max*motor.Kt; %最大转矩
motor.ACC_max = motor.T_rated/motor.J*0.5;  %最大加速度

% 测量参数
motor.fric = 0.2*motor.Kt;          %静摩擦
motor.damp = motor.T_rated/motor.radps_max*0.01; %阻尼系数

%% 对拖平台
motor.J = motor.J*2;            %转动惯量x2
motor.damp = motor.damp*2;      %阻尼系数x2
motor.fric = motor.fric*2;      %静摩擦x2

%% 电机初始随机角度
motor.angle_init = 2*pi*rand(1);

%% 参数显示
disp(motor);