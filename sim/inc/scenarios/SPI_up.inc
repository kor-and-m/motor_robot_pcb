* ==== SCENARIO C: IMU (1.8V) -> ESP (3.3V) over U5 ====
R_SRC_MISO  nMISO  /IMU_ICM20948/SPI_MISO  10
V_MISO_DRV  nMISO  0  PWL( \
+ {T0} 0 \
+ {T0+1*Tclk} 0 \
+ {T0+2*Tclk} 0 \
+ {T0+3*Tclk} {V18} \
+ {T0+4*Tclk} {V18} \
+ {T0+5*Tclk} {V18} \
+ {T0+6*Tclk} {V18} \
+ {T0+7*Tclk} 0 \
+ {T0+8*Tclk} 0 )

.meas tran tpd_MISO  TRIG V(/imu_icm20948/spi_miso)     VAL={0.7*V18} RISE=1 \
                    TARG V(/levelshift_spi5/MISO_3V3)  VAL={VIH33}    RISE=1
.meas tran MISO_ESP_MAX MAX V(/levelshift_spi5/MISO_3V3) FROM {T0+2*Tclk} TO {T0+8*Tclk}
.meas tran MISO_ESP_MIN MIN V(/levelshift_spi5/MISO_3V3) FROM {T0+2*Tclk} TO {T0+8*Tclk}
