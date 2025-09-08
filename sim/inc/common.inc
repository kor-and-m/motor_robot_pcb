* ===== COMMON (общие для всех сценариев) =====

* --- Повторяем режимы, которые включает KiCad GUI ---
.control
  set ngbehavior=ps
  set ngbehavior=lt
  set ngbehavior=a
.endc

* Параметры шин
.param V33=3.3  V18=1.8

R_GNDTIE  GND  0  1m

* Узлы питания — подсказка .op (ускоряет сходимость, не фиксирует жёстко)
.nodeset V(vlogic)=3.2 V(vlogic_rf)=3.2 V(vio18)=1.7 V(vlogic_mpu)=3.2
.ic V(VLOGIC)=0 V(VIO18)=0 V(/imu_icm20948/imu_cs)=0

* Сходимость/интегратор/точность
.option method=gear rshunt=1e12 gmin=1e-12 reltol=1e-3 abstol=1e-9 vntol=1e-6 itl1=500 itl4=200

* Что сохраняем (одно для всех сценариев)
.save V(vlogic) V(vlogic_rf) V(vio18)
.save V(/levelshift_spi5/INT_3V3) V(/imu_icm20948/imu_int)
.save I(V1) @L1[i]
