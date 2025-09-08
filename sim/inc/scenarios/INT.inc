* ==== SCENARIO A: IMU INT (1.8В) -> ESP (3.3В) через уровень ====

* Порог для приёмника 3.3В
.param VIH33=2.0

* Транзиент (длительности можно менять при необходимости)
.tran 1u 12m 0 2u

* Дадим питанию подняться до фронта
.param T0=5m

* --- Измерения ---
* Надёжные детекторы фронта через CROSS (избегаем “=VAL out of interval”)
.meas tran t_src WHEN ( V(/imu_icm20948/imu_int)      - {0.7*V18} )  CROSS=1
.meas tran t_dst WHEN ( V(/levelshift_spi5/INT_3V3)   - {VIH33}   )  CROSS=1

* Улетит в MISS, если t_src/t_dst нет — это нормально (нет фронта => нет задержки)
.meas tran tpd_INT  PARAM='t_dst - t_src'

* Амплитуды для диагностики (видно, почему нет t_dst, если порог не достигается)
.meas tran INT3V3_MAX  MAX  V(/levelshift_spi5/INT_3V3) FROM={T0}       TO=12m
.meas tran INT18_MIN   MIN  V(/imu_icm20948/imu_int)    FROM={T0}       TO=12m

* Быстрые sanity-чекапсы шин
.meas tran V33_AT2m     FIND V(vlogic)                    AT=2m
.meas tran V18_AT2m     FIND V(vio18)                     AT=2m
.meas tran VINT3V3_At6m FIND V(/levelshift_spi5/INT_3V3) AT={T0+1m}
