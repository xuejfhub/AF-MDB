%% 设置电机参数
motor = struct();
motor.V_rated = 36;
motor.rpm_rated = 3000;    %额定转速
motor.rpm_max = 4000;    %最高转速
motor.radps_rated = motor.rpm_rated*2*pi/60;    %额定转速
motor.radps_max = motor.rpm_max*2*pi/60;    %最高转速
motor.power_rated = 200;                    %额定功率
motor.P = 4;    %极对数
motor.Rs = 0.1/2;     %相电阻    
motor.Ld = 0.35e-3/2;   %d轴电感
motor.Lq = 0.35e-3/2;   %q轴电感
motor.Ke = 4.6; %反电动势系数
motor.J = 18.9e-6;          %转动惯量

%% 编码器参数
motor.ENC_CNT =2500*4;  %2500线双边沿采样
