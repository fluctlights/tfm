================
=INFO DE ESTADO=
================

Primer comando que me ha funcionado, para generar un sistema completo, esta deprecated la funcion pero funciona:

build/ARM/gem5.opt -d m5out/estadisticas configs/deprecated/example/fs.py  \
--bootloader=/home/fluctlights/Pi4-Kernel/ALTERNATIVO/aarch-system-20220707/binaries/boot.arm64 \
--disk-image=/home/fluctlights/Pi4-Kernel/ALTERNATIVO/ubuntu-18.04-arm64-docker.img \
--dtb=/home/fluctlights/Escritorio/Repos/tfm/gem5/m5out/system.dtb \
--kernel=/home/fluctlights/Pi4-Kernel/ALTERNATIVO/aarch-system-20220707/binaries/vmlinux.arm64 \
--num-cpus=4 --mem-type=LPDDR2_S4_1066_1x32 \
--mem-size=1GB \
--caches --l2cache --l2_size=512kB --l1i_size=16kB --l1d_size=16kB \
--cpu-clock=1.4GHz --sys-clock=1.4GHz \
--timesync


ESTO ME CREA UNA SESION CORRECTAMENTE CON:

./util/term/m5term <port> normalmente port es 3456 y me genera ademas puertos UART, que creo que se pueden usar

Revisar a ver si puedo sacar un bootloader para raspberry pi directamente sin tirar de genericos de gem5
CREO QUE ESO NO VA A PODER SER PERO SI PUEDO MIRAR FORMAS DE MODIFICAR EL COMPORTAMIENTO PARA QUE SEA MAS RAPIDO
HAY UN VIDEO DE UNO HACIENDO UNA RPI4 -> https://pierreay.github.io/reproduce-spectre-gem5/

TAMBIEN PUEDO MIRAR LA PARTE DE MODIFICACION DEL MENUCONFIG A VER QUE SACO:
https://blog.carreralinux.com.ar/2017/12/configurar-el-kernel-make-menuconfig/

Warnings obtenidos:

**** REAL SIMULATION ****
src/dev/arm/energy_ctrl.cc:252: warn: Existing EnergyCtrl, but no enabled DVFSHandler found.
src/sim/simulate.cc:194: info: Entering event queue @ 0.  Starting simulation...
src/dev/arm/rv_ctrl.cc:176: warn: SCReg: Access to unknown device dcc0:site0:pos0:fn7:dev0
src/arch/arm/insts/pseudo.cc:172: warn:         instruction 'csdb' unimplemented
src/dev/arm/gic_v2.cc:747: warn: GIC APRn write ignored because not implemented: 0xd0
src/dev/arm/gic_v2.cc:747: warn: GIC APRn write ignored because not implemented: 0xd4
src/dev/arm/gic_v2.cc:747: warn: GIC APRn write ignored because not implemented: 0xd8
src/dev/arm/gic_v2.cc:747: warn: GIC APRn write ignored because not implemented: 0xdc
src/dev/arm/gic_v2.cc:747: warn: GIC APRn write ignored because not implemented: 0xd0
src/dev/arm/gic_v2.cc:747: warn: GIC APRn write ignored because not implemented: 0xd4
src/dev/arm/gic_v2.cc:747: warn: GIC APRn write ignored because not implemented: 0xd8
src/dev/arm/gic_v2.cc:747: warn: GIC APRn write ignored because not implemented: 0xdc
src/dev/arm/gic_v2.cc:747: warn: GIC APRn write ignored because not implemented: 0xd0
src/dev/arm/gic_v2.cc:747: warn: GIC APRn write ignored because not implemented: 0xd4
src/dev/arm/gic_v2.cc:747: warn: GIC APRn write ignored because not implemented: 0xd8
src/dev/arm/gic_v2.cc:747: warn: GIC APRn write ignored because not implemented: 0xdc
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
240188324082: system.terminal: attach terminal 0
src/sim/power_state.cc:118: warn: PowerState: More than one power state change request encountered within the same simulation tick
src/sim/power_state.cc:118: warn: PowerState: More than one power state change request encountered within the same simulation tick
src/sim/power_state.cc:118: warn: PowerState: More than one power state change request encountered within the same simulation tick
src/dev/arm/rv_ctrl.cc:122: warn: Tried to read RealView I/O at offset 0x8 that doesn't exist
src/dev/arm/rv_ctrl.cc:122: warn: Tried to read RealView I/O at offset 0x48 that doesn't exist
src/sim/power_state.cc:118: warn: PowerState: More than one power state change request encountered within the same simulation tick
src/sim/power_state.cc:118: warn: PowerState: More than one power state change request encountered within the same simulation tick
src/dev/arm/energy_ctrl.cc:77: warn: EnergyCtrl: Disabled handler, ignoring read from reg 0

Log de esta run:

==== m5 terminal: Terminal 0 ====
[    0.000000] Booting Linux on physical CPU 0x0000000000 [0x410fd070]
[    0.000000] Linux version 4.18.0+ (arm-employee@arm-computer) (gcc version 7.4.0 (Ubuntu/Linaro 7.4.0-1ubuntu1~18.04.1)) #1 SMP PREEMPT Wed Nov 6 14:10:00 GMT 2019
[    0.000000] Machine model: V2P-CA15
[    0.000000] Memory limited to 1024MB
[    0.000000] cma: Reserved 16 MiB at 0x000000009f000000
[    0.000000] On node 0 totalpages: 131072
[    0.000000]   DMA32 zone: 2048 pages used for memmap
[    0.000000]   DMA32 zone: 0 pages reserved
[    0.000000]   DMA32 zone: 131072 pages, LIFO batch:31
[    0.000000] random: get_random_bytes called from start_kernel+0xa8/0x3e8 with crng_init=0
[    0.000000] percpu: Embedded 23 pages/cpu @(____ptrval____) s53976 r8192 d32040 u94208
[    0.000000] pcpu-alloc: s53976 r8192 d32040 u94208 alloc=23*4096
[    0.000000] pcpu-alloc: [0] 0 [0] 1 [0] 2 [0] 3 
[    0.000000] Detected PIPT I-cache on CPU0
[    0.000000] CPU features: enabling workaround for ARM erratum 832075
[    0.000000] CPU features: enabling workaround for ARM erratum 834220
[    0.000000] CPU features: enabling workaround for EL2 vector hardening
[    0.000000] CPU features: detected: Kernel page table isolation (KPTI)
[    0.000000] Built 1 zonelists, mobility grouping on.  Total pages: 129024
[    0.000000] Kernel command line: earlyprintk=pl011,0x1c090000 console=ttyAMA0 lpj=19988480 norandmaps rw loglevel=8 mem=1GB root=/dev/sda1
[    0.000000] log_buf_len individual max cpu contribution: 4096 bytes
[    0.000000] log_buf_len total cpu_extra contributions: 12288 bytes
[    0.000000] log_buf_len min size: 16384 bytes
[    0.000000] log_buf_len: 32768 bytes
[    0.000000] early log buf free: 14724(89%)
[    0.000000] Dentry cache hash table entries: 65536 (order: 7, 524288 bytes)
[    0.000000] Inode-cache hash table entries: 32768 (order: 6, 262144 bytes)
[    0.000000] Memory: 479836K/524288K available (6910K kernel code, 452K rwdata, 2312K rodata, 448K init, 217K bss, 28068K reserved, 16384K cma-reserved)
[    0.000000] SLUB: HWalign=64, Order=0-3, MinObjects=0, CPUs=4, Nodes=1
[    0.000000] Preemptible hierarchical RCU implementation.
[    0.000000] 	RCU restricting CPUs from NR_CPUS=256 to nr_cpu_ids=4.
[    0.000000] 	Tasks RCU enabled.
[    0.000000] RCU: Adjusting geometry for rcu_fanout_leaf=16, nr_cpu_ids=4
[    0.000000] NR_IRQS: 64, nr_irqs: 64, preallocated irqs: 0
[    0.000000] GIC: GICv2 detected, but range too small and irqchip.gicv2_force_probe not set
[    0.000000] clk_gem5_energy_ctrl: No cpu-map in DT! Falling back to old detection method!
[    0.000000] clk_gem5_energy_ctrl: No clusters in DT! Falling back to using CPU topology!
[    0.000002] sched_clock: 32 bits at 24MHz, resolution 41ns, wraps every 89478484971ns
[    0.000118] arch_timer: Unable to find a suitable frame in timer @ 0x000000002a810000
[    0.000123] Failed to initialize '/timer@2a810000': -22
[    0.000202] Console: colour dummy device 80x25
[    0.000209] Calibrating delay loop (skipped) preset value.. 9994.24 BogoMIPS (lpj=19988480)
[    0.000216] pid_max: default: 32768 minimum: 301
[    0.000269] Mount-cache hash table entries: 1024 (order: 1, 8192 bytes)
[    0.000275] Mountpoint-cache hash table entries: 1024 (order: 1, 8192 bytes)
[    0.024100] ASID allocator initialised with 128 entries
[    0.032099] Hierarchical SRCU implementation.
[    0.048115] smp: Bringing up secondary CPUs ...
[    0.080155] Detected PIPT I-cache on CPU1
[    0.080169] CPU1: Booted secondary processor 0x0000000001 [0x410fd070]
[    0.112186] Detected PIPT I-cache on CPU2
[    0.112201] CPU2: Booted secondary processor 0x0000000002 [0x410fd070]
[    0.144218] Detected PIPT I-cache on CPU3
[    0.144233] CPU3: Booted secondary processor 0x0000000003 [0x410fd070]
[    0.144275] smp: Brought up 1 node, 4 CPUs
[    0.144290] SMP: Total of 4 processors activated.
[    0.144295] CPU features: detected: Privileged Access Never
[    0.144299] CPU features: detected: User Access Override
[    0.144304] CPU features: detected: 32-bit EL0 Support
[    0.144308] CPU features: detected: Scalable Vector Extension
[    0.145383] SVE: maximum available vector length 16 bytes per vector
[    0.145387] SVE: default vector length 16 bytes per vector
[    0.145391] CPU: All CPU(s) started at EL2
[    0.145400] alternatives: patching kernel code
[    0.146309] devtmpfs: initialized
[    0.147430] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 7645041785100000 ns
[    0.147436] futex hash table entries: 1024 (order: 4, 65536 bytes)
[    0.148449] NET: Registered protocol family 16
[    0.228765] cpuidle: using governor menu
[    0.228884] vdso: 2 pages (1 code @ (____ptrval____), 1 data @ (____ptrval____))
[    0.228890] hw-breakpoint: found 16 breakpoint and 16 watchpoint registers.
[    0.229468] DMA: preallocated 256 KiB pool for atomic allocations
[    0.229472] Serial: AMBA PL011 UART driver
[    0.229678] OF: amba_device_add() failed (-2) for /watchdog@2a490000
[    0.229933] OF: amba_device_add() failed (-2) for /watchdog@2b060000
[    0.230066] 1c090000.uart: ttyAMA0 at MMIO 0x1c090000 (irq = 13, base_baud = 0) is a PL011 rev3
[    0.230487] console [ttyAMA0] enabled
[    0.230697] 1c0a0000.uart: ttyAMA1 at MMIO 0x1c0a0000 (irq = 14, base_baud = 0) is a PL011 rev3
[    0.230912] 1c0b0000.uart: ttyAMA2 at MMIO 0x1c0b0000 (irq = 15, base_baud = 0) is a PL011 rev3
[    0.231126] 1c0c0000.uart: ttyAMA3 at MMIO 0x1c0c0000 (irq = 16, base_baud = 0) is a PL011 rev3
[    0.231285] OF: amba_device_add() failed (-2) for /kmi@1c060000
[    0.231359] OF: amba_device_add() failed (-2) for /kmi@1c070000
[    0.231433] OF: /watchdog@1c0f0000: could not find phandle
[    0.231441] ERROR: could not get clock /watchdog@1c0f0000:apb_pclk(1)
[    0.231450] OF: amba_device_add() failed (-2) for /watchdog@1c0f0000
[    0.231524] OF: /rtc@1c170000: could not find phandle
[    0.231532] ERROR: could not get clock /rtc@1c170000:apb_pclk(0)
[    0.231541] OF: amba_device_add() failed (-2) for /rtc@1c170000
[    0.235495] HugeTLB registered 2.00 MiB page size, pre-allocated 0 pages
[    0.235721] vgaarb: loaded
[    0.235850] SCSI subsystem initialized
[    0.235910] libata version 3.00 loaded.
[    0.236005] usbcore: registered new interface driver usbfs
[    0.236032] usbcore: registered new interface driver hub
[    0.236058] usbcore: registered new device driver usb
[    0.236097] pps_core: LinuxPPS API ver. 1 registered
[    0.236103] pps_core: Software ver. 5.3.6 - Copyright 2005-2007 Rodolfo Giometti <giometti@linux.it>
[    0.236118] PTP clock support registered
[    0.239688] NET: Registered protocol family 2
[    0.239904] tcp_listen_portaddr_hash hash table entries: 256 (order: 0, 4096 bytes)
[    0.239916] TCP established hash table entries: 4096 (order: 3, 32768 bytes)
[    0.239956] TCP bind hash table entries: 4096 (order: 4, 65536 bytes)
[    0.239996] TCP: Hash tables configured (established 4096 bind 4096)
[    0.240026] UDP hash table entries: 256 (order: 1, 8192 bytes)
[    0.240040] UDP-Lite hash table entries: 256 (order: 1, 8192 bytes)
[    0.240099] NET: Registered protocol family 1
[    0.240339] RPC: Registered named UNIX socket transport module.
[    0.240345] RPC: Registered udp transport module.
[    0.240352] RPC: Registered tcp transport module.
[    0.240358] RPC: Registered tcp NFSv4.1 backchannel transport module.
[    0.240366] PCI: CLS 0 bytes, default 64
[    0.240654] kvm [1]: SVE system without VHE unsupported.  Broken cpu?
[    0.241057] workingset: timestamp_bits=62 max_order=17 bucket_order=0
[    0.244495] squashfs: version 4.0 (2009/01/31) Phillip Lougher
[    0.244775] fuse init (API version 7.27)
[    0.245136] io scheduler noop registered
[    0.245241] io scheduler cfq registered (default)
[    0.245248] io scheduler mq-deadline registered
[    0.245254] io scheduler kyber registered
[    0.245290] atomic64_test: passed
[    0.245645] pci-host-generic 30000000.pci: host bridge /pci ranges:
[    0.245655] pci-host-generic 30000000.pci:   No bus range found for /pci, using [bus 00-ff]
[    0.245665] pci-host-generic 30000000.pci: Parsing ranges property...
[    0.245678] pci-host-generic 30000000.pci:    IO 0x2f000000..0x2f00ffff -> 0x00000000
[    0.245691] pci-host-generic 30000000.pci:   MEM 0x40000000..0x7fffffff -> 0x00000000
[    0.245718] pci-host-generic 30000000.pci: ECAM at [mem 0x30000000-0x3fffffff] for [bus 00-ff]
[    0.245778] pci-host-generic 30000000.pci: PCI host bridge to bus 0000:00
[    0.245788] pci_bus 0000:00: root bus resource [bus 00-ff]
[    0.245797] pci_bus 0000:00: root bus resource [io  0x0000-0xffff]
[    0.245807] pci_bus 0000:00: root bus resource [mem 0x40000000-0x7fffffff] (bus address [0x00000000-0x3fffffff])
[    0.245817] pci_bus 0000:00: scanning bus
[    0.245842] pci 0000:00:01.0: [8086:7111] type 00 class 0x010185
[    0.245856] pci 0000:00:01.0: reg 0x10: [io  0x0000-0x0007]
[    0.245866] pci 0000:00:01.0: reg 0x14: [io  0x0000-0x0003]
[    0.245876] pci 0000:00:01.0: reg 0x18: [io  0x0000-0x0007]
[    0.245887] pci 0000:00:01.0: reg 0x1c: [io  0x0000-0x0003]
[    0.245897] pci 0000:00:01.0: reg 0x20: [io  0x0000-0x000f]
[    0.245909] pci 0000:00:01.0: reg 0x30: [mem 0x40000000-0x400007ff pref]
[    0.246317] pci_bus 0000:00: fixups for bus
[    0.246325] pci_bus 0000:00: bus scan returning with max=00
[    0.246337] pci 0000:00:01.0: BAR 6: assigned [mem 0x40000000-0x400007ff pref]
[    0.246347] pci 0000:00:01.0: BAR 4: assigned [io  0x1000-0x100f]
[    0.246357] pci 0000:00:01.0: BAR 0: assigned [io  0x1010-0x1017]
[    0.246368] pci 0000:00:01.0: BAR 2: assigned [io  0x1018-0x101f]
[    0.246378] pci 0000:00:01.0: BAR 1: assigned [io  0x1020-0x1023]
[    0.246389] pci 0000:00:01.0: BAR 3: assigned [io  0x1024-0x1027]
[    0.247931] Serial: 8250/16550 driver, 4 ports, IRQ sharing disabled
[    0.249072] ata_piix 0000:00:01.0: assign IRQ: got 23
[    0.249081] ata_piix 0000:00:01.0: version 2.13
[    0.249091] ata_piix 0000:00:01.0: enabling device (0000 -> 0001)
[    0.249122] ata_piix 0000:00:01.0: enabling bus mastering
[    0.249746] scsi host0: ata_piix
[    0.252296] scsi host1: ata_piix
[    0.252373] ata1: PATA max UDMA/33 cmd 0x1010 ctl 0x1020 bmdma 0x1000 irq 23
[    0.252381] ata2: PATA max UDMA/33 cmd 0x1018 ctl 0x1024 bmdma 0x1008 irq 23
[    0.252652] libphy: Fixed MDIO Bus: probed
[    0.252675] e1000: Intel(R) PRO/1000 Network Driver - version 7.3.21-k8-NAPI
[    0.252682] e1000: Copyright (c) 1999-2006 Intel Corporation.
[    0.252710] e1000e: Intel(R) PRO/1000 Network Driver - 3.2.6-k
[    0.252717] e1000e: Copyright(c) 1999 - 2015 Intel Corporation.
[    0.252746] igb: Intel(R) Gigabit Ethernet Network Driver - version 5.4.0-k
[    0.252753] igb: Copyright (c) 2007-2014 Intel Corporation.
[    0.252782] ixgbe: Intel(R) 10 Gigabit PCI Express Network Driver - version 5.1.0-k
[    0.252790] ixgbe: Copyright (c) 1999-2016 Intel Corporation.
[    0.252848] ixgbevf: Intel(R) 10 Gigabit PCI Express Virtual Function Network Driver - version 4.1.0-k
[    0.252856] ixgbevf: Copyright (c) 2009 - 2015 Intel Corporation.
[    0.256332] i40e: Intel(R) Ethernet Connection XL710 Network Driver - version 2.3.2-k
[    0.256340] i40e: Copyright (c) 2013 - 2014 Intel Corporation.
[    0.256425] ixgb: Intel(R) PRO/10GbE Network Driver - version 1.0.135-k2-NAPI
[    0.256432] ixgb: Copyright (c) 1999-2008 Intel Corporation.
[    0.256462] i40evf: Intel(R) 40-10 Gigabit Virtual Function Network Driver - version 3.2.2-k
[    0.256470] Copyright (c) 2013 - 2015 Intel Corporation.
[    0.256711] usbcore: registered new interface driver usb-storage
[    0.256962] mousedev: PS/2 mouse device common for all mice
[    0.257072] gem5 DVFS handler is disabled
[    0.257079] gem5-energy-ctrl loaded at (____ptrval____)
[    0.257086] gem5_energy_ctrl_mc: gem5_mc_init: DVFS handler in energy controller is disabled,                         ARM gem5 multi-cluster cpufreq driver                         will not be registered
[    0.257481] usbcore: registered new interface driver usbhid
[    0.257487] usbhid: USB HID core driver
[    0.257559] NET: Registered protocol family 17
[    0.412431] ata1.00: ATA-7: M5 IDE Disk, , max UDMA/66
[    0.412438] ata1.00: 3906250 sectors, multi 0: LBA 
[    0.412558] scsi 0:0:0:0: Direct-Access     ATA      M5 IDE Disk      n/a  PQ: 0 ANSI: 5
[    0.412881] sd 0:0:0:0: Attached scsi generic sg0 type 0
[    0.412913] sd 0:0:0:0: [sda] 3906250 512-byte logical blocks: (2.00 GB/1.86 GiB)
[    0.412935] sd 0:0:0:0: [sda] Write Protect is off
[    0.412944] sd 0:0:0:0: [sda] Mode Sense: 00 3a 00 00
[    0.412979] sd 0:0:0:0: [sda] Write cache: disabled, read cache: enabled, doesn't support DPO or FUA
[    0.413343]  sda: sda1
[    0.413670] sd 0:0:0:0: [sda] Attached SCSI disk
[    0.417534] EXT4-fs (sda1): mounted filesystem with ordered data mode. Opts: (null)
[    0.417549] VFS: Mounted root (ext4 filesystem) on device 8:1.
[    0.417642] devtmpfs: mounted
[    0.417724] Freeing unused kernel memory: 448K
+ mount -t proc - /proc
+ mount -t sysfs - /sys
+ mount -t debugfs - /sys/kernel/debug/
+ [ -e /dev/sdb1 ]
+ [ -e /dev/sdb ]
+ [ -e /dev/vdb1 ]
+ [ -e /dev/vdb ]
+ [ -e /dev/vda1 ]
+ [ -e /dev/vda ]
+ f=/tmp/script
+ /sbin/m5 readfile
+ [ -s /tmp/script ]
+ exec /sbin/getty -a root -L ttyAMA0 vt102

Ubuntu 18.04.2 LTS aarch64-gem5 ttyAMA0

aarch64-gem5 login: root (automatic login)

[    0.453838] random: fast init done

=====================================================================================================================


