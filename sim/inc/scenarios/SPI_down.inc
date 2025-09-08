* ==== SCENARIO B: ESP -> IMU over downshift ====
V_SCLK  /levelshift_spi5/SCLK_3V3  0  PULSE(0 {V33} {T0} 4n 4n {Thigh} {Tclk})
V_CS    /levelshift_spi5/CS_3V3    0  PULSE({V33} 0 {T0-0.5*Tclk} 4n 4n {8*Tclk} {20*Tclk})
V_MOSI  /levelshift_spi5/MOSI_3V3  0  PWL( \
+ {T0} 0 \
+ {T0+0*Tclk} {V33} \
+ {T0+1*Tclk} 0 \
+ {T0+2*Tclk} {V33} \
+ {T0+3*Tclk} 0 \
+ {T0+4*Tclk} 0 \
+ {T0+5*Tclk} {V33} \
+ {T0+6*Tclk} 0 \
+ {T0+7*Tclk} {V33} \
+ {T0+8*Tclk} 0 )

.meas tran SCLK_IMU_MAX MAX V(/imu_icm20948/imu_cs)   FROM {T0+2*Tclk} TO {T0+8*Tclk}
.meas tran SCLK_IMU_MIN MIN V(/imu_icm20948/imu_cs)   FROM {T0+2*Tclk} TO {T0+8*Tclk}
.meas tran MOSI_IMU_MAX MAX V(/imu_icm20948/spi_mosi) FROM {T0+2*Tclk} TO {T0+8*Tclk}
.meas tran MOSI_IMU_MIN MIN V(/imu_icm20948/spi_mosi) FROM {T0+2*Tclk} TO {T0+8*Tclk}
