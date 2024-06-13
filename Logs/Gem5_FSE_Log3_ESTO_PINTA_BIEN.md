
===================================================
CONFIGURACION DE UNA IMPLEMENTACION DE UN ARM O3CPU 
===================================================

# 1.- QUE ARCHIVOS SON DE O3CPU?

GEM5 PROPORCIONA UN ARCHIVO BASADO EN UN ARMV7A; 
SIN EMBARGO, ES EXTRAPOLABLE AL ARMV8A PORQUE PUEDE ARRANCAR CON 64BIT (PROBADO)
LA IDEA ES CONFIGURAR ESTE ARCHIVO, QUE ES VALIDO, PARA QUE SE PAREZCA A UN CORTEX A72

	$ nano /ruta/absoluta/gem5/configs/common/cores/arm/O3_ARM_v7a.py
	
EL QUE ESTE ARCHIVO SEA VALIDO PARA ESTE PROPOSITO ES GENIAL _PORQUE NO TENDREMOS QUE CREAR NUEVOS OBJECTS_

# 2.- MODIFICACION DE FICHEROS

AQUI DENTRO TENDREMOS QUE MODIFICAR AQUELLOS PARÁMETROS QUE SEAN DISTINTOS AL CORTEX A72
COMO REFERENCIAS SE HA COGIDO LA TECHNICAL REFERENCE DEL CORTEX A72 Y UNA PAGINA QUE LO RESUME
	ENLACE PAGINA :: ¿?

# 3.- RECOMPILACION DE GEM5

UNA VEZ MODIFICADOS LOS PARAMETROS DENTRO DEL FICHERO HAY QUE RECOMPILAR TODO GEM5

	$ scons ./build/ARM/gem5.opt

NO TARDA TANTO COMO LA PRIMERA VEZ, PERO ES RECOMENDABLE CERRAR VENTANAS INNECESARIAS
UNA VEZ REALIZADA ESTAMOS LISTOS PARA EJECUTAR


===============================================
EJECUCION DE UNA IMPLEMENTACION DE UN ARM O3CPU 
===============================================

ANTES DE CONTINUAR, DECIR QUE LANZAR UNA SIMULACION NUEVA ES MUY COSTOSO EN TERMINOS DE TIEMPO Y DE COMPUTO
LO MAS RECOMENDABLE ES CERRAR PROCESOS ANTES DE LANZARLA


# 1.- CONFIGURAR EL M5_PATH

ESTE PASO ES IMPORTANTE -> SETEA TODOS LOS PARAMETROS NECESARIOS DEL SISTEMA DE UNA
MUY INTERESANTE SI SE OLVIDA ALGUN PARAMETRO NECESARIO PARA ARRANCAR EL SISTEMA (BOOTLOADER, DTB, ETC)
M5_PATH ES LA VARIABLE QUE GEM5 UTILIZA PARA BUSCAR TODOS ESTOS ARCHIVOS E INCLUIRLOS EN EL COMANDO

	$ export M5_PATH=/home/fluctlights/Pi4-Kernel/ALTERNATIVO/aarch-system-20220707


# 2.- LANZAR EL COMANDO

CON ESTE COMANDO LANZAMOS LA SIMULACION
POR AHORA SE TIENE EN CUENTA TODO EL TIEMPO DE LA SIMULACION
LA IDEA ES TENER EN CUENTA SOLO EL TIEMPO DE EJECUCION DEL BINARIO


	$ ./build/ARM/gem5.opt configs/example/arm/starter_fs.py --cpu="o3" --num-cores=1 --disk-image=$M5_PATH/disks/ubuntu-18.04-arm64-docker.img --root-device=/dev/vda1 --script ./cpu_tests/benchmarks/bin/arm/Bubblesort
	
	$ ./build/ARM/gem5.opt configs/example/arm/starter_fs.py --cpu="o3" --num-cores=1 --disk-image=$M5_PATH/disks/ubuntu-18.04-arm64-docker.img --root-device=/dev/vda1 --script ./cpu_tests/benchmarks/bin/arm/holamundo


# 3.- LA SALIDA DEL COMANDO:

gem5 Simulator System.  https://www.gem5.org
gem5 is copyrighted software; use the --copyright option for details.

gem5 version 23.0.1.0
gem5 compiled Feb  2 2024 09:18:00
gem5 started Feb  2 2024 09:36:32
gem5 executing on hamilton, pid 2482153
command line: ./build/ARM/gem5.opt configs/example/arm/starter_fs.py --cpu=o3 --num-cores=1 --disk-image=/home/fluctlights/Pi4-Kernel/ALTERNATIVO/aarch-system-20220707/disks/ubuntu-18.04-arm64-docker.img --root-device=/dev/vda1 --script ./cpu_tests/benchmarks/bin/arm/Bubblesort

warn: The `get_runtime_isa` function is deprecated. Please migrate away from using this function.
Global frequency set at 1000000000000 ticks per second
src/mem/dram_interface.cc:690: warn: DRAM device capacity (8192 Mbytes) does not match the address range assigned (2048 Mbytes)
src/sim/kernel_workload.cc:46: info: kernel located at: /home/fluctlights/Pi4-Kernel/ALTERNATIVO/aarch-system-20220707/binaries/vmlinux.arm64
src/base/statistics.hh:279: warn: One of the stats is a legacy stat. Legacy stat is a stat that does not belong to any statistics::Group. Legacy stat is deprecated.
system.vncserver: Listening for connections on port 5900
system.terminal: Listening for connections on port 3456
system.realview.uart1.device: Listening for connections on port 3457
system.realview.uart2.device: Listening for connections on port 3458
system.realview.uart3.device: Listening for connections on port 3459
system.remote_gdb: Listening for connections on port 7000
src/arch/arm/fs_workload.cc:121: info: Using bootloader at address 0x10
src/arch/arm/fs_workload.cc:139: info: Using kernel entry physical address at 0x80080000
src/arch/arm/linux/fs_workload.cc:111: info: Loading DTB file: m5out/system.dtb at address 0x88000000
src/dev/arm/energy_ctrl.cc:252: warn: Existing EnergyCtrl, but no enabled DVFSHandler found.
src/sim/simulate.cc:194: info: Entering event queue @ 0.  Starting simulation...
src/dev/arm/rv_ctrl.cc:176: warn: SCReg: Access to unknown device dcc0:site0:pos0:fn7:dev0
11457210750: system.terminal: attach terminal 0
13659139500: system.terminal: detach terminal 0
13825073750: system.terminal: attach terminal 0
14109831250: system.terminal: detach terminal 0
23270867500: system.terminal: attach terminal 0
src/arch/arm/insts/pseudo.cc:172: warn: 	instruction 'csdb' unimplemented
src/dev/arm/gic_v2.cc:747: warn: GIC APRn write ignored because not implemented: 0xd0
src/dev/arm/gic_v2.cc:747: warn: GIC APRn write ignored because not implemented: 0xd4
src/dev/arm/gic_v2.cc:747: warn: GIC APRn write ignored because not implemented: 0xd8
src/dev/arm/gic_v2.cc:747: warn: GIC APRn write ignored because not implemented: 0xdc
src/dev/arm/rv_ctrl.cc:122: warn: Tried to read RealView I/O at offset 0x60 that doesn't exist
src/dev/arm/rv_ctrl.cc:122: warn: Tried to read RealView I/O at offset 0x48 that doesn't exist
src/dev/arm/rv_ctrl.cc:198: warn: Tried to write RVIO at offset 0xa8 (data 0) that doesn't exist
src/dev/arm/rv_ctrl.cc:198: warn: Tried to write RVIO at offset 0xa8 (data 0) that doesn't exist
src/dev/arm/rv_ctrl.cc:198: warn: Tried to write RVIO at offset 0xa8 (data 0) that doesn't exist
src/dev/arm/rv_ctrl.cc:198: warn: Tried to write RVIO at offset 0xa8 (data 0) that doesn't exist
src/dev/arm/rv_ctrl.cc:198: warn: Tried to write RVIO at offset 0xa8 (data 0) that doesn't exist
src/dev/arm/rv_ctrl.cc:198: warn: Tried to write RVIO at offset 0xa8 (data 0) that doesn't exist
src/dev/arm/rv_ctrl.cc:198: warn: Tried to write RVIO at offset 0xa8 (data 0) that doesn't exist
src/dev/arm/rv_ctrl.cc:198: warn: Tried to write RVIO at offset 0xa8 (data 0) that doesn't exist
src/dev/arm/rv_ctrl.cc:198: warn: Tried to write RVIO at offset 0xa8 (data 0) that doesn't exist
src/dev/arm/rv_ctrl.cc:198: warn: Tried to write RVIO at offset 0xa8 (data 0) that doesn't exist
src/dev/arm/rv_ctrl.cc:122: warn: Tried to read RealView I/O at offset 0x8 that doesn't exist
src/dev/arm/rv_ctrl.cc:122: warn: Tried to read RealView I/O at offset 0x48 that doesn't exist
src/dev/arm/energy_ctrl.cc:77: warn: EnergyCtrl: Disabled handler, ignoring read from reg 0


============================================
SALIDA POR PANTALLA TRAS EJECUTAR EL COMANDO 
============================================

# 1.- SALIDA POR PANTALLA

PARA ESTE PASO HAY QUE CONECTARSE A LA SESION QUE ABRE GEM5 PARA VER SU TERMINAL
PUEDE HACERSE TANTO CON LA HERRAMIENTA INTEGRADA DE GEM5 COMO LA GENERICA TELNET
LOS EJEMPLOS SON CON TELNET PERO LA SALIDA SERIA IDENTICA


fluctlights@hamilton:~/Escritorio/Repos/tfm/gem5/util$ telnet localhost 3456
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
==== m5 terminal: Terminal 0 ====
[    0.000000] Booting Linux on physical CPU 0x0000000000 [0x410fd070]
[    0.000000] Linux version 4.18.0+ (arm-employee@arm-computer) (gcc version 7.4.0 (Ubuntu/Linaro 7.4.0-1ubuntu1~18.04.1)) #1 SMP PREEMPT Wed Nov 6 14:10:00 GMT 2019
[    0.000000] Machine model: V2P-CA15
[    0.000000] Memory limited to 2048MB
[    0.000000] cma: Reserved 16 MiB at 0x00000000ff000000
[    0.000000] random: get_random_bytes called from start_kernel+0xa8/0x3e8 with crng_init=0
[    0.000000] percpu: Embedded 23 pages/cpu @(____ptrval____) s53976 r8192 d32040 u94208
[    0.000000] Detected PIPT I-cache on CPU0
[    0.000000] CPU features: enabling workaround for ARM erratum 832075
[    0.000000] CPU features: enabling workaround for ARM erratum 834220
[    0.000000] CPU features: enabling workaround for EL2 vector hardening
[    0.000000] CPU features: detected: Kernel page table isolation (KPTI)
[    0.000000] Built 1 zonelists, mobility grouping on.  Total pages: 516096
[    0.000000] Kernel command line: console=ttyAMA0 lpj=19988480 norandmaps root=/dev/vda1 rw mem=2GB
[    0.000000] Dentry cache hash table entries: 262144 (order: 9, 2097152 bytes)
[    0.000000] Inode-cache hash table entries: 131072 (order: 8, 1048576 bytes)
[    0.000000] Memory: 2034324K/2097152K available (6910K kernel code, 452K rwdata, 2312K rodata, 448K init, 217K bss, 46444K reserved, 16384K cma-reserved)
[    0.000000] SLUB: HWalign=64, Order=0-3, MinObjects=0, CPUs=1, Nodes=1
[    0.000000] Preemptible hierarchical RCU implementation.
[    0.000000] 	RCU restricting CPUs from NR_CPUS=256 to nr_cpu_ids=1.
[    0.000000] 	Tasks RCU enabled.
[    0.000000] RCU: Adjusting geometry for rcu_fanout_leaf=16, nr_cpu_ids=1
[    0.000000] NR_IRQS: 64, nr_irqs: 64, preallocated irqs: 0
[    0.000000] GIC: GICv2 detected, but range too small and irqchip.gicv2_force_probe not set
[    0.000000] clk_gem5_energy_ctrl: No cpu-map in DT! Falling back to old detection method!
[    0.000000] clk_gem5_energy_ctrl: No clusters in DT! Falling back to using CPU topology!
[    0.000001] sched_clock: 32 bits at 24MHz, resolution 41ns, wraps every 89478484971ns
[    0.000065] arch_timer: cp15 and mmio timer(s) running at 25.16MHz (phys/virt).
[    0.000069] clocksource: arch_sys_counter: mask: 0xffffffffffffff max_cycles: 0x5cdd39714, max_idle_ns: 440795202620 ns
[    0.000072] sched_clock: 56 bits at 25MHz, resolution 39ns, wraps every 4398046511084ns
[    0.000106] Console: colour dummy device 80x25
[    0.000112] Calibrating delay loop (skipped) preset value.. 9994.24 BogoMIPS (lpj=19988480)
[    0.000116] pid_max: default: 32768 minimum: 301
[    0.000139] Mount-cache hash table entries: 4096 (order: 3, 32768 bytes)
[    0.000144] Mountpoint-cache hash table entries: 4096 (order: 3, 32768 bytes)
[    0.024072] ASID allocator initialised with 128 entries
[    0.032069] Hierarchical SRCU implementation.
[    0.048079] smp: Bringing up secondary CPUs ...
[    0.048082] smp: Brought up 1 node, 1 CPU
[    0.048084] SMP: Total of 1 processors activated.
[    0.048087] CPU features: detected: Privileged Access Never
[    0.048088] CPU features: detected: User Access Override
[    0.048090] CPU features: detected: 32-bit EL0 Support
[    0.048092] CPU features: detected: Scalable Vector Extension
[    0.049825] SVE: maximum available vector length 16 bytes per vector
[    0.049827] SVE: default vector length 16 bytes per vector
[    0.049829] CPU: All CPU(s) started at EL2
[    0.049832] alternatives: patching kernel code
[    0.050398] devtmpfs: initialized
[    0.050854] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 7645041785100000 ns
[    0.050859] futex hash table entries: 256 (order: 2, 16384 bytes)
[    0.051393] NET: Registered protocol family 16
[    0.132176] cpuidle: using governor menu
[    0.132216] vdso: 2 pages (1 code @ (____ptrval____), 1 data @ (____ptrval____))
[    0.132220] hw-breakpoint: found 16 breakpoint and 16 watchpoint registers.
[    0.132462] DMA: preallocated 256 KiB pool for atomic allocations
[    0.132465] Serial: AMBA PL011 UART driver
[    0.132582] OF: amba_device_add() failed (-2) for /watchdog@2a490000
[    0.132672] OF: amba_device_add() failed (-2) for /watchdog@2b060000
[    0.132737] 1c090000.uart: ttyAMA0 at MMIO 0x1c090000 (irq = 13, base_baud = 0) is a PL011 rev3
[    0.134872] console [ttyAMA0] enabled
[    0.135113] 1c0a0000.uart: ttyAMA1 at MMIO 0x1c0a0000 (irq = 14, base_baud = 0) is a PL011 rev3
[    0.135294] 1c0b0000.uart: ttyAMA2 at MMIO 0x1c0b0000 (irq = 15, base_baud = 0) is a PL011 rev3
[    0.135479] 1c0c0000.uart: ttyAMA3 at MMIO 0x1c0c0000 (irq = 16, base_baud = 0) is a PL011 rev3
[    0.135622] OF: amba_device_add() failed (-2) for /kmi@1c060000
[    0.135680] OF: amba_device_add() failed (-2) for /kmi@1c070000
[    0.135739] OF: /watchdog@1c0f0000: could not find phandle
[    0.135771] ERROR: could not get clock /watchdog@1c0f0000:apb_pclk(1)
[    0.135808] OF: amba_device_add() failed (-2) for /watchdog@1c0f0000
[    0.135867] OF: /rtc@1c170000: could not find phandle
[    0.135897] ERROR: could not get clock /rtc@1c170000:apb_pclk(0)
[    0.135931] OF: amba_device_add() failed (-2) for /rtc@1c170000
[    0.148540] HugeTLB registered 2.00 MiB page size, pre-allocated 0 pages
[    0.152448] vgaarb: loaded
[    0.152521] SCSI subsystem initialized
[    0.156277] usbcore: registered new interface driver usbfs
[    0.156319] usbcore: registered new interface driver hub
[    0.156358] usbcore: registered new device driver usb
[    0.156404] pps_core: LinuxPPS API ver. 1 registered
[    0.156433] pps_core: Software ver. 5.3.6 - Copyright 2005-2007 Rodolfo Giometti <giometti@linux.it>
[    0.156487] PTP clock support registered
[    0.156915] clocksource: Switched to clocksource arch_sys_counter
[    0.159572] NET: Registered protocol family 2
[    0.159728] tcp_listen_portaddr_hash hash table entries: 1024 (order: 2, 16384 bytes)
[    0.159778] TCP established hash table entries: 16384 (order: 5, 131072 bytes)
[    0.159867] TCP bind hash table entries: 16384 (order: 6, 262144 bytes)
[    0.159992] TCP: Hash tables configured (established 16384 bind 16384)
[    0.160067] UDP hash table entries: 1024 (order: 3, 32768 bytes)
[    0.160119] UDP-Lite hash table entries: 1024 (order: 3, 32768 bytes)
[    0.160197] NET: Registered protocol family 1
[    0.173813] RPC: Registered named UNIX socket transport module.
[    0.173850] RPC: Registered udp transport module.
[    0.173878] RPC: Registered tcp transport module.
[    0.173905] RPC: Registered tcp NFSv4.1 backchannel transport module.
[    0.174081] kvm [1]: SVE system without VHE unsupported.  Broken cpu?
[    0.174432] workingset: timestamp_bits=62 max_order=19 bucket_order=0
[    0.175788] squashfs: version 4.0 (2009/01/31) Phillip Lougher
[    0.182379] fuse init (API version 7.27)
[    0.182838] io scheduler noop registered
[    0.182907] io scheduler cfq registered (default)
[    0.182935] io scheduler mq-deadline registered
[    0.182962] io scheduler kyber registered
[    0.183021] atomic64_test: passed
[    0.183358] pci-host-generic 30000000.pci: host bridge /pci ranges:
[    0.183397] pci-host-generic 30000000.pci:   No bus range found for /pci, using [bus 00-ff]
[    0.183450] pci-host-generic 30000000.pci:    IO 0x2f000000..0x2f00ffff -> 0x00000000
[    0.183497] pci-host-generic 30000000.pci:   MEM 0x40000000..0x7fffffff -> 0x00000000
[    0.183552] pci-host-generic 30000000.pci: ECAM at [mem 0x30000000-0x3fffffff] for [bus 00-ff]
[    0.183627] pci-host-generic 30000000.pci: PCI host bridge to bus 0000:00
[    0.183668] pci_bus 0000:00: root bus resource [bus 00-ff]
[    0.183700] pci_bus 0000:00: root bus resource [io  0x0000-0xffff]
[    0.183736] pci_bus 0000:00: root bus resource [mem 0x40000000-0x7fffffff] (bus address [0x00000000-0x3fffffff])
[    0.183945] pci 0000:00:01.0: BAR 6: assigned [mem 0x40000000-0x400007ff pref]
[    0.183988] pci 0000:00:01.0: BAR 0: assigned [io  0x1000-0x101f]
[    0.184155] virtio-pci 0000:00:01.0: enabling device (0000 -> 0001)
[    0.184194] virtio-pci 0000:00:01.0: virtio_pci: leaving for legacy driver
[    0.185793] Serial: 8250/16550 driver, 4 ports, IRQ sharing disabled
[    0.186553] virtio_blk virtio0: [vda] 3906250 512-byte logical blocks (2.00 GB/1.86 GiB)
[    0.190932]  vda: vda1
[    0.203723] libphy: Fixed MDIO Bus: probed
[    0.203762] e1000: Intel(R) PRO/1000 Network Driver - version 7.3.21-k8-NAPI
[    0.203802] e1000: Copyright (c) 1999-2006 Intel Corporation.
[    0.203845] e1000e: Intel(R) PRO/1000 Network Driver - 3.2.6-k
[    0.203878] e1000e: Copyright(c) 1999 - 2015 Intel Corporation.
[    0.203922] igb: Intel(R) Gigabit Ethernet Network Driver - version 5.4.0-k
[    0.203961] igb: Copyright (c) 2007-2014 Intel Corporation.
[    0.204003] ixgbe: Intel(R) 10 Gigabit PCI Express Network Driver - version 5.1.0-k
[    0.204046] ixgbe: Copyright (c) 1999-2016 Intel Corporation.
[    0.208539] ixgbevf: Intel(R) 10 Gigabit PCI Express Virtual Function Network Driver - version 4.1.0-k
[    0.208592] ixgbevf: Copyright (c) 2009 - 2015 Intel Corporation.
[    0.212715] i40e: Intel(R) Ethernet Connection XL710 Network Driver - version 2.3.2-k
[    0.212759] i40e: Copyright (c) 2013 - 2014 Intel Corporation.
[    0.216854] ixgb: Intel(R) PRO/10GbE Network Driver - version 1.0.135-k2-NAPI
[    0.216895] ixgb: Copyright (c) 1999-2008 Intel Corporation.
[    0.216937] i40evf: Intel(R) 40-10 Gigabit Virtual Function Network Driver - version 3.2.2-k
[    0.216984] Copyright (c) 2013 - 2015 Intel Corporation.
[    0.221152] usbcore: registered new interface driver usb-storage
[    0.221357] mousedev: PS/2 mouse device common for all mice
[    0.221457] gem5 DVFS handler is disabled
[    0.221481] gem5-energy-ctrl loaded at (____ptrval____)
[    0.221512] gem5_energy_ctrl_mc: gem5_mc_init: DVFS handler in energy controller is disabled,                         ARM gem5 multi-cluster cpufreq driver                         will not be registered
[    0.221766] usbcore: registered new interface driver usbhid
[    0.221799] usbhid: USB HID core driver
[    0.221862] NET: Registered protocol family 17
[    0.228162] EXT4-fs (vda1): mounted filesystem with ordered data mode. Opts: (null)
[    0.228218] VFS: Mounted root (ext4 filesystem) on device 254:1.
[    0.228339] devtmpfs: mounted
[    0.228449] Freeing unused kernel memory: 448K
+ mount -t proc - /proc
+ mount -t sysfs - /sys
+ mount -t debugfs - /sys/kernel/debug/
+ [ -e /dev/sdb1 ]
+ [ -e /dev/sdb ]
+ [ -e /dev/vdb1 ]
+ [ -e /dev/vdb ]
+ [ -e /dev/vda1 ]
+ mount /dev/vda1 /data
[    0.236040] random: fast init done
+ break
+ f=/tmp/script
+ /sbin/m5 readfile
+ [ -s /tmp/script ]
+ chmod +rx /tmp/script
+ /tmp/script
-50000
+ exec /sbin/getty -a root -L ttyAMA0 vt102

Ubuntu 18.04.2 LTS aarch64-gem5 ttyAMA0

aarch64-gem5 login: root (automatic login)

Welcome to Ubuntu 18.04.2 LTS (GNU/Linux 4.18.0+ aarch64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/advantage
This system has been minimized by removing packages and content that are
not required on a system that users do not log into.

To restore this content, you can run the 'unminimize' command.

The programs included with the Ubuntu system are free software;
the exact distribution terms for each program are described in the
individual files in /usr/share/doc/*/copyright.

Ubuntu comes with ABSOLUTELY NO WARRANTY, to the extent permitted by
applicable law.

root@aarch64-gem5:~#


====================================
PASOS A REALIZAR TRAS ESTA EJECUCION
====================================

# 1.- TRATAR DE USAR EL DTB PROPIO DE LA RASPBERRY PI 4

EL DTB DEFINE LA ESTRUCTURA DE DISPOSITIVOS DE UN SISTEMA COMPLETO
EL DEFINIR UNO PROPIO Y NO UNO GENERICO DE GEM5 MEJORA LA SIMULACIÓN
DESGRACIADAMENTE CASI CON TOTAL SEGURIDAD SEA IMPOSIBLE DE REALIZAR

TRAS REALIZAR DIFERENTES PRUEBAS INTEGRANDO UN DTB DEL RPI4 DA KERNEL PANIC
SEGURAMENTE TENGA QUE VER CON EL TIPO DE MÁQUINA (--machine-type=VExpress_GEM5_V1)

# 2.- USAR UN BINARIO GENERADO CON LA RASPBERRY PI 4

SE TIENE UN HELLOWORLD COMPILADO CON LA RASPBERRY PI 4
SE COMPILO DE FORMA ESTATICA! ESTE ASPECTO ES IMPORTANTE
PARA EVITAR OPTIMIZACIONES QUE PUDIERA REALIZAR PARA LA RPI4
CAMBIAR EL PARAMETRO --script Y PONER ESTE BINARIO PARA REALIZAR ESTO

# 3.- CONTAR ÚNICAMENTE CICLOS DE EJECUCION DEL SCRIPT

HASTA ESTE MOMENTO LAS SIMULACIONES CUENTAN TODO EL TIEMPO DE PROCESADOR
LO QUE SE QUIERE ES QUE SOLO SE CUENTE EL TIEMPO DE EJECUCION DEL SCRIPT

_ESTO TODAVIA NO SE SABE COMO HACERLO!_

PERO SE TIENE UNA REFERENCIA DE CÓMO DEBERÍA SER
HAY UNA COSA LLAMADA M5OPS QUE PERMITEN REALIZAR FUNCIONES ESPECIFICAS
TENGO UN PAPER QUE EXPLICA COMO USAR M5OPS EN UNA APLICACION REAL
TODAVIA NO HE HECHO PRUEBAS

# 4.- INSERTAR LOS MODULOS DE ENERGIA EN LA SIMULACION

EN LA DOCUMENTACION VIENEN UNOS SCRIPTS QUE INCLUYEN EL MATHPWREXPRMODEL
SERIA INCLUIRLOS EN EL SCRIPT DE EJECUCION PARA SACAR SUS METRICAS TAMBIEN

PARA ELLO TRAS REALIZAR MODIFICACIONES ES NECESARIO RECOMPILAR GEM5

	$ scons ./build/ARM/gem5.opt

UNA VEZ REALIZADA ESTAMOS LISTOS PARA EJECUTAR
EN STATS.TXT DEBERIA DE APARECER NUEVOS CAMPOS RELACIONADOS CON CONSUMO

# 5.- CONFIGURAR DVFS PARA ASEMEJARSE MÁS A LA REALIDAD

LA RPI4 UTILIZA TÉCNICAS DE MODIFICACION DE VOLTAJE PARA AHORRAR ENERGÍA
LO IDEAL ES QUE EN LA SIMULACIÓN TAMBIÉN SE TENGA EN CUENTA ESTO

EN LA DOCUMENTACIÓN APARECE ESTO Y ADEMÁS EN EL CÓDIGO DEL SCRIPT DE EJECUCION
SERÍA BÁSICAMENTE DEFINIR UN RANGO DE VOLTAJES Y EL SIMULADOR IRÁ SELECCIONANDOLOS 
EN FUNCION DEL ESTADO EN CADA CICLO (MUY RELACIONADO CON EL MODELO DE ENERGIA)

# 6.- DEFINIR PUNTOS DE ESTADO

GEM5 PERMITE DEFINIR ESTADOS DE SIMULACIÓN MUY PRECISOS
ESTO PERMITIRÍA CREAR LA SIMULACIÓN Y GUARDAR EL ESTADO
ASI SIEMPRE TIRARIAMOS DE ESE ESTADO Y AHORRAMOS TIEMPO

ESTO PUEDE IR MUY RELACIONADO CON EL TEMA DE CONTAR CICLOS DE EJECUCIÓN CONCRETOS
SE HACE CON LAS M5OPS TAMBIEN, PERO NO SE COMO SE HACE EXACTAMENTE
LA MEGADOCUMENTACION TIENE COSAS RELACIONADAS CON ESTO PERO TODAVIA ME FALTA ENTENDERLO





