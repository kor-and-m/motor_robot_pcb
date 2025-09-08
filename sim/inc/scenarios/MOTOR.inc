* ==== SCENARIO D: Motor drive basic check ====
.param RM1=4  LM1=150u
RM1  Net-_J_M1-Pin_1_  Net-_J_M1-Pin_2_  {RM1}
LM1  Net-_J_M1-Pin_1_  Net-_J_M1-Pin_2_  {LM1}

V_AIN1  /drv8833rty/m1_in1  0  PULSE(0 {V33} {T0} 20n 20n 2m 4m)
V_AIN2  /drv8833rty/m1_in2  0  0

.meas tran VM1_DIFF AVG V(Net-_J_M1-Pin_1_, Net-_J_M1-Pin_2_) FROM {T0+1m} TO {T0+3m}
.meas tran IM1_RMS  RMS I(RM1) FROM {T0+1m} TO {T0+3m}
