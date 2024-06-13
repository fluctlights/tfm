
=========================================================
IMPLEMENTACION DEL MODELO DE ENERGIA DE GEM5 EN ARM O3CPU 
=========================================================

# 1.- QUE ES LO PRIMERO QUE HAY QUE HACER?

GEM5 PROPORCIONA UN MODELO DE ENERGIA POR DEFECTO BASADO EN ESTADOS DE PROCESADOR
EN LA DOCUMENTACION SE ESPECIFICA COMO LLAMAR A ESTE MODELO EN PYTHON
VIENE DE BASE EN GEM5 POR LO QUE NO HAY QUE CREAR UN OBJETO NUEVO Y COMPILARLO
AUN ASI ES BUENA PRACTICA RECOMPILAR AL HACER CAMBIOS EN FICHEROS
NO TARDA APENAS Y SUELE ELIMINAR PROBLEMAS
	


# 2.- INTRODUCIR LAS CLASES DEL MODELO DE ENERGIA

PARA PODER UTILIZAR EL MODELO DE ENERGIA ES NECESARIO METER LAS CLASES EN EL
FICHERO QUE CARGA LA SIMULACION. 

SIMPLEMENTE METER TODAS ELLAS DE UNA EN UNA E IR COMPILANDO DE VEZ EN CUANDO

	$ scons ./build/ARM/gem5.opt
	
SI DA FALLOS, VOLVER A LA VERSION SIN CLASES AÑADIDAS Y PROBAR DE NUEVO

===============================================
EJECUCION DE UNA IMPLEMENTACION DE UN ARM O3CPU 
===============================================

ANTES DE CONTINUAR, DECIR QUE LANZAR UNA SIMULACION NUEVA ES MUY COSTOSO EN TERMINOS DE TIEMPO Y DE COMPUTO
LO MAS RECOMENDABLE ES CERRAR PROCESOS ANTES DE LANZARLA

# 1.- CONFIGURAR EL M5_PATH

SI POR ALGUNA RAZON SE CERRO LA SESION DE SHELL DONDE ESTABA DEFINIDA LA VARIABLE M5_PATH 
SERA NECESARIO METERLA DE NUEVO

	$ export M5_PATH=/home/fluctlights/Pi4-Kernel/ALTERNATIVO/aarch-system-20220707


# 2.- LANZAR EL COMANDO

CON ESTE COMANDO LANZAMOS LA SIMULACION
POR AHORA SE TIENE EN CUENTA TODO EL TIEMPO DE LA SIMULACION
LA IDEA ES TENER EN CUENTA SOLO EL TIEMPO DE EJECUCION DEL BINARIO

AHORA LA SIMULACION ES MAS PRECISA CON MEMORIAS DDR4, SINGLE CHANNEL, DE 4GB, Y UNA VELOCIDAD DE CLOCK DE 1.5GHz


	$ ./build/ARM/gem5.opt configs/example/arm/starter_fs.py --cpu="o3" --num-cores=1 --disk-image=$M5_PATH/disks/ubuntu-18.04-arm64-docker.img --root-device=/dev/vda1 --script ./cpu_tests/benchmarks/bin/arm/holamundo --mem-type DDR4_2400_8x8 --mem-size 4GB --cpu-freq 1.5GHz


# 3.- LA SALIDA DEL COMANDO:

==== m5 terminal: Terminal 0 ====
[    0.000000] Booting Linux on physical CPU 0x0000000000 [0x410fd070]
[    0.000000] Linux version 4.18.0+ (arm-employee@arm-computer) (gcc version 7.4.0 (Ubuntu/Linaro 7.4.0-1ubuntu1~18.04.1)) #1 SMP PREEMPT Wed Nov 6 14:10:00 GMT 2019
[    0.000000] Machine model: V2P-CA15
[    0.000000] Memory limited to 4096MB
[    0.000000] cma: Reserved 16 MiB at 0x00000000ff000000
[    0.000000] random: get_random_bytes called from start_kernel+0xa8/0x3e8 with crng_init=0
[    0.000000] percpu: Embedded 23 pages/cpu @(____ptrval____) s53976 r8192 d32040 u94208
[    0.000000] Detected PIPT I-cache on CPU0
[    0.000000] CPU features: enabling workaround for ARM erratum 832075
[    0.000000] CPU features: enabling workaround for ARM erratum 834220
[    0.000000] CPU features: enabling workaround for EL2 vector hardening
[    0.000000] CPU features: detected: Kernel page table isolation (KPTI)
[    0.000000] Built 1 zonelists, mobility grouping on.  Total pages: 1032192
[    0.000000] Kernel command line: console=ttyAMA0 lpj=19988480 norandmaps root=/dev/vda1 rw mem=4GB
[    0.000000] Dentry cache hash table entries: 524288 (order: 10, 4194304 bytes)
[    0.000000] Inode-cache hash table entries: 262144 (order: 9, 2097152 bytes)
[    0.000000] software IO TLB [mem 0xfafff000-0xfefff000] (64MB) mapped at [(____ptrval____)-(____ptrval____)]
[    0.000000] Memory: 4029680K/4194304K available (6910K kernel code, 452K rwdata, 2312K rodata, 448K init, 217K bss, 148240K reserved, 16384K cma-reserved)
[    0.000000] SLUB: HWalign=64, Order=0-3, MinObjects=0, CPUs=1, Nodes=1
[    0.000000] Preemptible hierarchical RCU implementation.
[    0.000000]  RCU restricting CPUs from NR_CPUS=256 to nr_cpu_ids=1.
[    0.000000]  Tasks RCU enabled.
[    0.000000] RCU: Adjusting geometry for rcu_fanout_leaf=16, nr_cpu_ids=1
[    0.000000] NR_IRQS: 64, nr_irqs: 64, preallocated irqs: 0
[    0.000000] GIC: GICv2 detected, but range too small and irqchip.gicv2_force_probe not set
[    0.000000] clk_gem5_energy_ctrl: No cpu-map in DT! Falling back to old detection method!
[    0.000000] clk_gem5_energy_ctrl: No clusters in DT! Falling back to using CPU topology!
[    0.000003] sched_clock: 32 bits at 24MHz, resolution 41ns, wraps every 89478484971ns
[    0.000165] arch_timer: Unable to find a suitable frame in timer @ 0x000000002a810000
[    0.000174] Failed to initialize '/timer@2a810000': -22
[    0.000269] Console: colour dummy device 80x25
[    0.000284] Calibrating delay loop (skipped) preset value.. 9994.24 BogoMIPS (lpj=19988480)
[    0.000294] pid_max: default: 32768 minimum: 301
[    0.000367] Mount-cache hash table entries: 8192 (order: 4, 65536 bytes)
[    0.000382] Mountpoint-cache hash table entries: 8192 (order: 4, 65536 bytes)
[    0.024171] ASID allocator initialised with 128 entries
[    0.032169] Hierarchical SRCU implementation.
[    0.048197] smp: Bringing up secondary CPUs ...
[    0.048205] smp: Brought up 1 node, 1 CPU
[    0.048211] SMP: Total of 1 processors activated.
[    0.048219] CPU features: detected: Privileged Access Never
[    0.048225] CPU features: detected: User Access Override
[    0.048231] CPU features: detected: 32-bit EL0 Support
[    0.048237] CPU features: detected: Scalable Vector Extension
[    0.050743] SVE: maximum available vector length 16 bytes per vector
[    0.050749] SVE: default vector length 16 bytes per vector
[    0.050755] CPU: All CPU(s) started at EL2
[    0.050766] alternatives: patching kernel code
[    0.052284] devtmpfs: initialized
[    0.053658] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 7645041785100000 ns
[    0.053669] futex hash table entries: 256 (order: 2, 16384 bytes)
[    0.055029] NET: Registered protocol family 16
[    0.136433] cpuidle: using governor menu
[    0.136543] vdso: 2 pages (1 code @ (____ptrval____), 1 data @ (____ptrval____))
[    0.136553] hw-breakpoint: found 16 breakpoint and 16 watchpoint registers.
[    0.137204] DMA: preallocated 256 KiB pool for atomic allocations
[    0.137211] Serial: AMBA PL011 UART driver
[    0.137517] OF: amba_device_add() failed (-2) for /watchdog@2a490000
[    0.137845] OF: amba_device_add() failed (-2) for /watchdog@2b060000
[    0.138036] 1c090000.uart: ttyAMA0 at MMIO 0x1c090000 (irq = 13, base_baud = 0) is a PL011 rev3
[    0.140960] console [ttyAMA0] enabled
[    0.141378] 1c0a0000.uart: ttyAMA1 at MMIO 0x1c0a0000 (irq = 14, base_baud = 0) is a PL011 rev3
[    0.141806] 1c0b0000.uart: ttyAMA2 at MMIO 0x1c0b0000 (irq = 15, base_baud = 0) is a PL011 rev3
[    0.142239] 1c0c0000.uart: ttyAMA3 at MMIO 0x1c0c0000 (irq = 16, base_baud = 0) is a PL011 rev3
[    0.142569] OF: amba_device_add() failed (-2) for /kmi@1c060000
[    0.142698] OF: amba_device_add() failed (-2) for /kmi@1c070000
[    0.142826] OF: /watchdog@1c0f0000: could not find phandle
[    0.142866] ERROR: could not get clock /watchdog@1c0f0000:apb_pclk(1)
[    0.142913] OF: amba_device_add() failed (-2) for /watchdog@1c0f0000
[    0.143040] OF: /rtc@1c170000: could not find phandle
[    0.143077] ERROR: could not get clock /rtc@1c170000:apb_pclk(0)
[    0.143121] OF: amba_device_add() failed (-2) for /rtc@1c170000
[    0.169007] HugeTLB registered 2.00 MiB page size, pre-allocated 0 pages
[    0.172936] vgaarb: loaded
[    0.173118] SCSI subsystem initialized
[    0.176708] usbcore: registered new interface driver usbfs
[    0.176775] usbcore: registered new interface driver hub
[    0.176836] usbcore: registered new device driver usb
[    0.176917] pps_core: LinuxPPS API ver. 1 registered
[    0.176953] pps_core: Software ver. 5.3.6 - Copyright 2005-2007 Rodolfo Giometti <giometti@linux.it>
[    0.177021] PTP clock support registered
[    0.189210] NET: Registered protocol family 2
[    0.189564] tcp_listen_portaddr_hash hash table entries: 2048 (order: 3, 32768 bytes)
[    0.189643] TCP established hash table entries: 32768 (order: 6, 262144 bytes)
[    0.189931] TCP bind hash table entries: 32768 (order: 7, 524288 bytes)
[    0.190244] TCP: Hash tables configured (established 32768 bind 32768)
[    0.190343] UDP hash table entries: 2048 (order: 4, 65536 bytes)
[    0.190430] UDP-Lite hash table entries: 2048 (order: 4, 65536 bytes)
[    0.190585] NET: Registered protocol family 1
[    0.200686] RPC: Registered named UNIX socket transport module.
[    0.200730] RPC: Registered udp transport module.
[    0.200763] RPC: Registered tcp transport module.
[    0.200797] RPC: Registered tcp NFSv4.1 backchannel transport module.
[    0.201170] kvm [1]: SVE system without VHE unsupported.  Broken cpu?
[    0.201987] workingset: timestamp_bits=62 max_order=20 bucket_order=0
[    0.211790] squashfs: version 4.0 (2009/01/31) Phillip Lougher
[    0.212833] fuse init (API version 7.27)
[    0.213965] io scheduler noop registered
[    0.214182] io scheduler cfq registered (default)
[    0.214218] io scheduler mq-deadline registered
[    0.214252] io scheduler kyber registered
[    0.214308] atomic64_test: passed
[    0.215214] pci-host-generic 30000000.pci: host bridge /pci ranges:
[    0.215264] pci-host-generic 30000000.pci:   No bus range found for /pci, using [bus 00-ff]
[    0.215335] pci-host-generic 30000000.pci:    IO 0x2f000000..0x2f00ffff -> 0x00000000
[    0.215394] pci-host-generic 30000000.pci:   MEM 0x40000000..0x7fffffff -> 0x00000000
[    0.215474] pci-host-generic 30000000.pci: ECAM at [mem 0x30000000-0x3fffffff] for [bus 00-ff]
[    0.215662] pci-host-generic 30000000.pci: PCI host bridge to bus 0000:00
[    0.215712] pci_bus 0000:00: root bus resource [bus 00-ff]
[    0.215754] pci_bus 0000:00: root bus resource [io  0x0000-0xffff]
[    0.215800] pci_bus 0000:00: root bus resource [mem 0x40000000-0x7fffffff] (bus address [0x00000000-0x3fffffff])
[    0.216440] pci 0000:00:01.0: BAR 6: assigned [mem 0x40000000-0x400007ff pref]
[    0.216492] pci 0000:00:01.0: BAR 0: assigned [io  0x1000-0x101f]
[    0.217587] virtio-pci 0000:00:01.0: enabling device (0000 -> 0001)
[    0.217636] virtio-pci 0000:00:01.0: virtio_pci: leaving for legacy driver
[    0.222464] Serial: 8250/16550 driver, 4 ports, IRQ sharing disabled
[    0.224270] virtio_blk virtio0: [vda] 3906250 512-byte logical blocks (2.00 GB/1.86 GiB)
[    0.228864]  vda: vda1
[    0.241303] libphy: Fixed MDIO Bus: probed
[    0.241362] e1000: Intel(R) PRO/1000 Network Driver - version 7.3.21-k8-NAPI
[    0.241410] e1000: Copyright (c) 1999-2006 Intel Corporation.
[    0.241479] e1000e: Intel(R) PRO/1000 Network Driver - 3.2.6-k
[    0.241519] e1000e: Copyright(c) 1999 - 2015 Intel Corporation.
[    0.241589] igb: Intel(R) Gigabit Ethernet Network Driver - version 5.4.0-k
[    0.241636] igb: Copyright (c) 2007-2014 Intel Corporation.
[    0.241704] ixgbe: Intel(R) 10 Gigabit PCI Express Network Driver - version 5.1.0-k
[    0.241756] ixgbe: Copyright (c) 1999-2016 Intel Corporation.
[    0.244831] ixgbevf: Intel(R) 10 Gigabit PCI Express Virtual Function Network Driver - version 4.1.0-k
[    0.244893] ixgbevf: Copyright (c) 2009 - 2015 Intel Corporation.
[    0.248832] i40e: Intel(R) Ethernet Connection XL710 Network Driver - version 2.3.2-k
[    0.248885] i40e: Copyright (c) 2013 - 2014 Intel Corporation.
[    0.252900] ixgb: Intel(R) PRO/10GbE Network Driver - version 1.0.135-k2-NAPI
[    0.252949] ixgb: Copyright (c) 1999-2008 Intel Corporation.
[    0.253018] i40evf: Intel(R) 40-10 Gigabit Virtual Function Network Driver - version 3.2.2-k
[    0.253074] Copyright (c) 2013 - 2015 Intel Corporation.
[    0.257056] usbcore: registered new interface driver usb-storage
[    0.257514] mousedev: PS/2 mouse device common for all mice
[    0.257716] gem5 DVFS handler is disabled
[    0.257748] gem5-energy-ctrl loaded at (____ptrval____)
[    0.257787] gem5_energy_ctrl_mc: gem5_mc_init: DVFS handler in energy controller is disabled,                         ARM gem5 multi-cluster cpufreq driver                         will not be registered
[    0.258397] usbcore: registered new interface driver usbhid
[    0.258437] usbhid: USB HID core driver
[    0.258560] NET: Registered protocol family 17
[    0.265225] EXT4-fs (vda1): mounted filesystem with ordered data mode. Opts: (null)
[    0.265298] VFS: Mounted root (ext4 filesystem) on device 254:1.
[    0.265490] devtmpfs: mounted
[    0.265647] Freeing unused kernel memory: 448K
+ mount -t proc - /proc
+ mount -t sysfs - /sys
+ mount -t debugfs - /sys/kernel/debug/
+ [ -e /dev/sdb1 ]
+ [ -e /dev/sdb ]
+ [ -e /dev/vdb1 ]
+ [ -e /dev/vdb ]
+ [ -e /dev/vda1 ]
+ mount /dev/vda1 /data
[    0.286003] random: fast init done
+ break
+ f=/tmp/script
+ /sbin/m5 readfile
+ [ -s /tmp/script ]
+ chmod +rx /tmp/script
+ /tmp/script
+ exec /sbin/getty -a root -L ttyAMA0 vt102

Ubuntu 18.04.2 LTS aarch64-gem5 ttyAMA0

aarch64-gem5 login: root (automatic login)


====================================
PASOS A REALIZAR TRAS ESTA EJECUCION
====================================

# 1.- TRATAR DE USAR EL DTB PROPIO DE LA RASPBERRY PI 4

PARA SABER QUE ES ESTO MIRAR EL LOG NUMERO 3

ACTUALMENTE SE SIGUE ESTANCADO EN EL TIPO DE MAQUINA ORIGINAL
TRAS REALIZAR DIFERENTES PRUEBAS INTEGRANDO UN DTB DEL RPI4 DA KERNEL PANIC
SEGURAMENTE TENGA QUE VER CON EL TIPO DE MÁQUINA (--machine-type=VExpress_GEM5_V1)

SE PUEDE PROBAR A INTRODUCIR NUEVOS PARAMETROS EN GEM5 AL CREAR EL SISTEMA
DEBERIA SER VIABLE. FALTA HACERLO POR AHORA


# 2.- CONTAR ÚNICAMENTE CICLOS DE EJECUCION DEL SCRIPT

HASTA ESTE MOMENTO LAS SIMULACIONES CUENTAN TODO EL TIEMPO DE PROCESADOR
LO QUE SE QUIERE ES QUE SOLO SE CUENTE EL TIEMPO DE EJECUCION DEL SCRIPT

SE TIENE UNA REFERENCIA DE CÓMO DEBERÍA SER -> M5OPS (LOG 3)
TENGO UN PAPER QUE EXPLICA COMO USAR M5OPS EN UNA APLICACION REAL

EN LA DOCUMENTACION DE GEM5 EXPLICAN EL PROCESO DE USO Y EN EL PAPER QUE ES CADA COSA
LA IDEA ES USAR AMBOS PARA HACERLO Y LUEGO PARA EXPLICARLO


# 3.- CONFIGURAR DVFS PARA ASEMEJARSE MÁS A LA REALIDAD

LA RPI4 UTILIZA TÉCNICAS DE MODIFICACION DE VOLTAJE PARA AHORRAR ENERGÍA
LO IDEAL ES QUE EN LA SIMULACIÓN TAMBIÉN SE TENGA EN CUENTA ESTO

EN LA DOCUMENTACIÓN APARECE ESTO Y ADEMÁS EN EL CÓDIGO DEL SCRIPT DE EJECUCION
SERÍA BÁSICAMENTE DEFINIR UN RANGO DE VOLTAJES Y EL SIMULADOR IRÁ SELECCIONANDOLOS 
EN FUNCION DEL ESTADO EN CADA CICLO (MUY RELACIONADO CON EL MODELO DE ENERGIA)

ESTO TODAVIA NO FUNCIONA CORRECTAMENTE! 
ESTOY EN ELLO

# 4.- DEFINIR PUNTOS DE ESTADO

GEM5 PERMITE DEFINIR ESTADOS DE SIMULACIÓN PRECISOS
ESTO PERMITIRÍA CREAR LA SIMULACIÓN Y GUARDAR EL ESTADO
ASI SIEMPRE TIRARIAMOS DE UN ESTADO INTERMEDIO Y AHORRAMOS TIEMPO

HAY REFERENCIAS EN INTERNET DE COMO HACER ESTO -> ALGO DE M5.INSTANCIATE(STATE)
HABRIA QUE METER NUEVAS OPCIONES Y CREAR UN CHECKPOINT ANTES
EL TRUCO AQUI ES INICIAR CON UNA CPU RAPIDA Y LUEGO GUARDAR EL CHECKPOINT
PARA LUEGO INCIAR CON LA PRECISA Y TARDAR MENOS

YO SEGURAMENTE HAGA EL CHECKPOINT CON LA PRECISA Y TIRARIA DE ELLA SIEMPRE

ESTO FUNCIONA CORRECTAMENTE YA, HACER UNA PRUEBA A SOLEDAD

	./build/ARM/gem5.opt configs/example/arm/starter_fs.py --cpu="o3" --num-cores=4 --disk-image=$M5_PATH/disks/ubuntu-expanded-arm64-docker.img --root-device=/dev/vda1 --script ./cpu_tests/benchmarks/bin/arm/script_inicio.sh --mem-type DDR4_2400_8x8 --mem-size 4GB --cpu-freq 1.5GHz --restore $GEM5_PATH/m5out/cpt.4789403947221/ --power-models

