================
# INFO DE ESTADO
================

Esta es la configuracion del ARM RSK para gem5, tras ver en la documentacion como hacerlo.

./build/ARM/gem5.opt configs/example/arm/starter_fs.py --cpu="hpi" --num-cores=1 --disk-image=$M5_PATH/disks/ubuntu-18.04-arm64-docker.img --root-device=/dev/vda1

Para esto ha sido necesario poner la variable M5_PATH=/home/fluctlights/Pi4-Kernel/ALTERNATIVO/aarch-system-20220707 --> HAY QUE HACER UN EXPORT

MAS INFORMACION MIRAR LA MEMORIA DEL 11 DE DICIEMBRE


### TIEMPOS DE STATS.TXT
INTERESANTE, AHORA PARECE QUE LOS CORES FUNCIONAN POR SEPARADO, LOS TIMES SON DISTINTOS:

$ cat stats.txt | grep system.cpu_cluster.cpus[0-3].power_state && cat stats.txt | grep system.cpu_cluster.cpus[0-3].idleCycles

system.cpu_cluster.cpus0.power_state.numTransitions        20356                       # Number of power state transitions (Count)
system.cpu_cluster.cpus0.power_state.ticksClkGated::samples        10178                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus0.power_state.ticksClkGated::mean 115544122.111613                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus0.power_state.ticksClkGated::stdev 71049267.654894                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus0.power_state.ticksClkGated::underflows         1087     10.68%     10.68% # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus0.power_state.ticksClkGated::1000-5e+10         9091     89.32%    100.00% # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus0.power_state.ticksClkGated::min_value          251                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus0.power_state.ticksClkGated::max_value    162568890                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus0.power_state.ticksClkGated::total        10178                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus0.power_state.pwrStateResidencyTicks::ON 139187877898                       # Cumulative time (in ticks) in various power states (Tick)
system.cpu_cluster.cpus0.power_state.pwrStateResidencyTicks::CLK_GATED 1176008074852                       # Cumulative time (in ticks) in various power states (Tick)
system.cpu_cluster.cpus1.power_state.numTransitions        16691                       # Number of power state transitions (Count)
system.cpu_cluster.cpus1.power_state.ticksClkGated::samples         8346                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus1.power_state.ticksClkGated::mean 155291097.592020                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus1.power_state.ticksClkGated::stdev 1194001397.710855                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus1.power_state.ticksClkGated::underflows          145      1.74%      1.74% # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus1.power_state.ticksClkGated::1000-5e+10         8199     98.24%     99.98% # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus1.power_state.ticksClkGated::5e+10-1e+11            2      0.02%    100.00% # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus1.power_state.ticksClkGated::min_value          250                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus1.power_state.ticksClkGated::max_value  79554746250                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus1.power_state.ticksClkGated::total         8346                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus1.power_state.pwrStateResidencyTicks::ON  19136452247                       # Cumulative time (in ticks) in various power states (Tick)
system.cpu_cluster.cpus1.power_state.pwrStateResidencyTicks::CLK_GATED 1296059500503                       # Cumulative time (in ticks) in various power states (Tick)
system.cpu_cluster.cpus2.power_state.numTransitions        16437                       # Number of power state transitions (Count)
system.cpu_cluster.cpus2.power_state.ticksClkGated::samples         8219                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus2.power_state.ticksClkGated::mean 156952439.689378                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus2.power_state.ticksClkGated::stdev 1253643562.246051                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus2.power_state.ticksClkGated::underflows          260      3.16%      3.16% # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus2.power_state.ticksClkGated::1000-5e+10         7957     96.81%     99.98% # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus2.power_state.ticksClkGated::5e+10-1e+11            2      0.02%    100.00% # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus2.power_state.ticksClkGated::min_value          251                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus2.power_state.ticksClkGated::max_value  79554736250                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus2.power_state.ticksClkGated::total         8219                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus2.power_state.pwrStateResidencyTicks::ON  25203850943                       # Cumulative time (in ticks) in various power states (Tick)
system.cpu_cluster.cpus2.power_state.pwrStateResidencyTicks::CLK_GATED 1289992101807                       # Cumulative time (in ticks) in various power states (Tick)
system.cpu_cluster.cpus3.power_state.numTransitions        16289                       # Number of power state transitions (Count)
system.cpu_cluster.cpus3.power_state.ticksClkGated::samples         8145                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus3.power_state.ticksClkGated::mean 156265186.021608                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus3.power_state.ticksClkGated::stdev 1308170653.928395                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus3.power_state.ticksClkGated::underflows          317      3.89%      3.89% # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus3.power_state.ticksClkGated::1000-5e+10         7826     96.08%     99.98% # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus3.power_state.ticksClkGated::5e+10-1e+11            2      0.02%    100.00% # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus3.power_state.ticksClkGated::min_value          251                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus3.power_state.ticksClkGated::max_value  79554693250                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus3.power_state.ticksClkGated::total         8145                       # Distribution of time spent in the clock gated state (Tick)
system.cpu_cluster.cpus3.power_state.pwrStateResidencyTicks::ON  42416012604                       # Cumulative time (in ticks) in various power states (Tick)
system.cpu_cluster.cpus3.power_state.pwrStateResidencyTicks::CLK_GATED 1272779940146                       # Cumulative time (in ticks) in various power states (Tick)
system.cpu_cluster.cpus0.idleCycles         354929675                       # Total number of cycles that the object has spent stopped (Unspecified)
system.cpu_cluster.cpus1.idleCycles          33286962                       # Total number of cycles that the object has spent stopped (Unspecified)
system.cpu_cluster.cpus2.idleCycles          45495271                       # Total number of cycles that the object has spent stopped (Unspecified)
system.cpu_cluster.cpus3.idleCycles          90653367                       # Total number of cycles that the object has spent stopped (Unspecified)

###WARNINGS OBTENIDOS:

warn: The `get_runtime_isa` function is deprecated. Please migrate away from using this function.
Global frequency set at 1000000000000 ticks per second
warn: No dot file generated. Please install pydot to generate the dot file and pdf.
src/mem/dram_interface.cc:690: warn: DRAM device capacity (8192 Mbytes) does not match the address range assigned (2048 Mbytes)
src/sim/kernel_workload.cc:46: info: kernel located at: /home/fluctlights/Pi4-Kernel/ALTERNATIVO/aarch-system-20220707/binaries/vmlinux.arm64
src/base/statistics.hh:279: warn: One of the stats is a legacy stat. Legacy stat is a stat that does not belong to any statistics::Group. Legacy stat is deprecated.
src/base/statistics.hh:279: warn: One of the stats is a legacy stat. Legacy stat is a stat that does not belong to any statistics::Group. Legacy stat is deprecated.
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass SimdDiv
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass SimdReduceAdd
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass SimdReduceAlu
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass SimdReduceCmp
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass SimdFloatReduceAdd
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass SimdFloatReduceCmp
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass SimdAes
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass SimdAesMix
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass SimdSha1Hash
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass SimdSha1Hash2
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass SimdSha256Hash
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass SimdSha256Hash2
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass SimdShaSigma2
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass SimdShaSigma3
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass SimdPredAlu
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass Matrix
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass MatrixMov
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass MatrixOP
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorUnitStrideLoad
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorUnitStrideStore
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorUnitStrideMaskLoad
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorUnitStrideMaskStore
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorStridedLoad
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorStridedStore
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorIndexedLoad
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorIndexedStore
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorUnitStrideFaultOnlyFirstLoad
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorWholeRegisterLoad
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorWholeRegisterStore
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorIntegerArith
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorFloatArith
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorFloatConvert
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorIntegerReduce
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorFloatReduce
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorMisc
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorIntegerExtension
src/cpu/minor/execute.cc:166: warn: No functional unit for OpClass VectorConfig
system.vncserver: Listening for connections on port 5901
system.terminal: Listening for connections on port 3460
system.realview.uart1.device: Listening for connections on port 3461
system.realview.uart2.device: Listening for connections on port 3462
system.realview.uart3.device: Listening for connections on port 3463
system.remote_gdb: Listening for connections on port 7001
src/arch/arm/fs_workload.cc:121: info: Using bootloader at address 0x10
src/arch/arm/fs_workload.cc:139: info: Using kernel entry physical address at 0x80080000
src/arch/arm/linux/fs_workload.cc:111: info: Loading DTB file: m5out/system.dtb at address 0x88000000
src/dev/arm/energy_ctrl.cc:252: warn: Existing EnergyCtrl, but no enabled DVFSHandler found.
src/sim/simulate.cc:194: info: Entering event queue @ 0.  Starting simulation...
src/dev/arm/rv_ctrl.cc:176: warn: SCReg: Access to unknown device dcc0:site0:pos0:fn7:dev0
6708372750: system.terminal: attach terminal 0
src/arch/arm/insts/pseudo.cc:172: warn:         instruction 'csdb' unimplemented
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

###SESION:

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
[    0.000002] sched_clock: 32 bits at 24MHz, resolution 41ns, wraps every 89478484971ns
[    0.000091] arch_timer: Unable to find a suitable frame in timer @ 0x000000002a810000
[    0.000097] Failed to initialize '/timer@2a810000': -22
[    0.000153] Console: colour dummy device 80x25
[    0.000163] Calibrating delay loop (skipped) preset value.. 9994.24 BogoMIPS (lpj=19988480)
[    0.000169] pid_max: default: 32768 minimum: 301
[    0.000222] Mount-cache hash table entries: 4096 (order: 3, 32768 bytes)
[    0.000246] Mountpoint-cache hash table entries: 4096 (order: 3, 32768 bytes)
[    0.024104] ASID allocator initialised with 128 entries
[    0.032102] Hierarchical SRCU implementation.
[    0.048116] smp: Bringing up secondary CPUs ...
[    0.048119] smp: Brought up 1 node, 1 CPU
[    0.048122] SMP: Total of 1 processors activated.
[    0.048126] CPU features: detected: Privileged Access Never
[    0.048129] CPU features: detected: User Access Override
[    0.048132] CPU features: detected: 32-bit EL0 Support
[    0.048135] CPU features: detected: Scalable Vector Extension
[    0.049632] SVE: maximum available vector length 16 bytes per vector
[    0.049634] SVE: default vector length 16 bytes per vector
[    0.049638] CPU: All CPU(s) started at EL2
[    0.049644] alternatives: patching kernel code
[    0.050448] devtmpfs: initialized
[    0.051156] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 7645041785100000 ns
[    0.051162] futex hash table entries: 256 (order: 2, 16384 bytes)
[    0.052081] NET: Registered protocol family 16
[    0.136247] cpuidle: using governor menu
[    0.136315] vdso: 2 pages (1 code @ (____ptrval____), 1 data @ (____ptrval____))
[    0.136321] hw-breakpoint: found 16 breakpoint and 16 watchpoint registers.
[    0.136794] DMA: preallocated 256 KiB pool for atomic allocations
[    0.136797] Serial: AMBA PL011 UART driver
[    0.136999] OF: amba_device_add() failed (-2) for /watchdog@2a490000
[    0.137146] OF: amba_device_add() failed (-2) for /watchdog@2b060000
[    0.137255] 1c090000.uart: ttyAMA0 at MMIO 0x1c090000 (irq = 13, base_baud = 0) is a PL011 rev3
[    0.139371] console [ttyAMA0] enabled
[    0.139757] 1c0a0000.uart: ttyAMA1 at MMIO 0x1c0a0000 (irq = 14, base_baud = 0) is a PL011 rev3
[    0.140016] 1c0b0000.uart: ttyAMA2 at MMIO 0x1c0b0000 (irq = 15, base_baud = 0) is a PL011 rev3
[    0.140319] 1c0c0000.uart: ttyAMA3 at MMIO 0x1c0c0000 (irq = 16, base_baud = 0) is a PL011 rev3
[    0.140525] OF: amba_device_add() failed (-2) for /kmi@1c060000
[    0.140598] OF: amba_device_add() failed (-2) for /kmi@1c070000
[    0.140672] OF: /watchdog@1c0f0000: could not find phandle
[    0.140706] ERROR: could not get clock /watchdog@1c0f0000:apb_pclk(1)
[    0.140745] OF: amba_device_add() failed (-2) for /watchdog@1c0f0000
[    0.140820] OF: /rtc@1c170000: could not find phandle
[    0.140851] ERROR: could not get clock /rtc@1c170000:apb_pclk(0)
[    0.140888] OF: amba_device_add() failed (-2) for /rtc@1c170000
[    0.160794] HugeTLB registered 2.00 MiB page size, pre-allocated 0 pages
[    0.164650] vgaarb: loaded
[    0.164749] SCSI subsystem initialized
[    0.168436] usbcore: registered new interface driver usbfs
[    0.168486] usbcore: registered new interface driver hub
[    0.168532] usbcore: registered new device driver usb
[    0.168593] pps_core: LinuxPPS API ver. 1 registered
[    0.168623] pps_core: Software ver. 5.3.6 - Copyright 2005-2007 Rodolfo Giometti <giometti@linux.it>
[    0.168682] PTP clock support registered
[    0.174476] NET: Registered protocol family 2
[    0.174708] tcp_listen_portaddr_hash hash table entries: 1024 (order: 2, 16384 bytes)
[    0.174772] TCP established hash table entries: 16384 (order: 5, 131072 bytes)
[    0.174988] TCP bind hash table entries: 16384 (order: 6, 262144 bytes)
[    0.175235] TCP: Hash tables configured (established 16384 bind 16384)
[    0.175379] UDP hash table entries: 1024 (order: 3, 32768 bytes)
[    0.175442] UDP-Lite hash table entries: 1024 (order: 3, 32768 bytes)
[    0.175541] NET: Registered protocol family 1
[    0.184648] RPC: Registered named UNIX socket transport module.
[    0.184689] RPC: Registered udp transport module.
[    0.184718] RPC: Registered tcp transport module.
[    0.184747] RPC: Registered tcp NFSv4.1 backchannel transport module.
[    0.185039] kvm [1]: SVE system without VHE unsupported.  Broken cpu?
[    0.185673] workingset: timestamp_bits=62 max_order=19 bucket_order=0
[    0.187920] squashfs: version 4.0 (2009/01/31) Phillip Lougher
[    0.192643] fuse init (API version 7.27)
[    0.193476] io scheduler noop registered
[    0.193600] io scheduler cfq registered (default)
[    0.193630] io scheduler mq-deadline registered
[    0.193658] io scheduler kyber registered
[    0.193707] atomic64_test: passed
[    0.194272] pci-host-generic 30000000.pci: host bridge /pci ranges:
[    0.194313] pci-host-generic 30000000.pci:   No bus range found for /pci, using [bus 00-ff]
[    0.194371] pci-host-generic 30000000.pci:    IO 0x2f000000..0x2f00ffff -> 0x00000000
[    0.194420] pci-host-generic 30000000.pci:   MEM 0x40000000..0x7fffffff -> 0x00000000
[    0.194484] pci-host-generic 30000000.pci: ECAM at [mem 0x30000000-0x3fffffff] for [bus 00-ff]
[    0.194610] pci-host-generic 30000000.pci: PCI host bridge to bus 0000:00
[    0.194652] pci_bus 0000:00: root bus resource [bus 00-ff]
[    0.194687] pci_bus 0000:00: root bus resource [io  0x0000-0xffff]
[    0.194725] pci_bus 0000:00: root bus resource [mem 0x40000000-0x7fffffff] (bus address [0x00000000-0x3fffffff])
[    0.195061] pci 0000:00:01.0: BAR 6: assigned [mem 0x40000000-0x400007ff pref]
[    0.195106] pci 0000:00:01.0: BAR 0: assigned [io  0x1000-0x101f]
[    0.195602] virtio-pci 0000:00:01.0: enabling device (0000 -> 0001)
[    0.195642] virtio-pci 0000:00:01.0: virtio_pci: leaving for legacy driver
[    0.198136] Serial: 8250/16550 driver, 4 ports, IRQ sharing disabled
[    0.201597] virtio_blk virtio0: [vda] 3906250 512-byte logical blocks (2.00 GB/1.86 GiB)
[    0.204698]  vda: vda1
[    0.216843] libphy: Fixed MDIO Bus: probed
[    0.216894] e1000: Intel(R) PRO/1000 Network Driver - version 7.3.21-k8-NAPI
[    0.216935] e1000: Copyright (c) 1999-2006 Intel Corporation.
[    0.216987] e1000e: Intel(R) PRO/1000 Network Driver - 3.2.6-k
[    0.217021] e1000e: Copyright(c) 1999 - 2015 Intel Corporation.
[    0.217075] igb: Intel(R) Gigabit Ethernet Network Driver - version 5.4.0-k
[    0.217116] igb: Copyright (c) 2007-2014 Intel Corporation.
[    0.217165] ixgbe: Intel(R) 10 Gigabit PCI Express Network Driver - version 5.1.0-k
[    0.217210] ixgbe: Copyright (c) 1999-2016 Intel Corporation.
[    0.220571] ixgbevf: Intel(R) 10 Gigabit PCI Express Virtual Function Network Driver - version 4.1.0-k
[    0.220625] ixgbevf: Copyright (c) 2009 - 2015 Intel Corporation.
[    0.224564] i40e: Intel(R) Ethernet Connection XL710 Network Driver - version 2.3.2-k
[    0.224609] i40e: Copyright (c) 2013 - 2014 Intel Corporation.
[    0.228593] ixgb: Intel(R) PRO/10GbE Network Driver - version 1.0.135-k2-NAPI
[    0.228635] ixgb: Copyright (c) 1999-2008 Intel Corporation.
[    0.228683] i40evf: Intel(R) 40-10 Gigabit Virtual Function Network Driver - version 3.2.2-k
[    0.228731] Copyright (c) 2013 - 2015 Intel Corporation.
[    0.232695] usbcore: registered new interface driver usb-storage
[    0.233014] mousedev: PS/2 mouse device common for all mice
[    0.233141] gem5 DVFS handler is disabled
[    0.233167] gem5-energy-ctrl loaded at (____ptrval____)
[    0.233199] gem5_energy_ctrl_mc: gem5_mc_init: DVFS handler in energy controller is disabled,                         ARM gem5 multi-cluster cpufreq driver                         will not be registered
[    0.233584] usbcore: registered new interface driver usbhid
[    0.233617] usbhid: USB HID core driver
[    0.233704] NET: Registered protocol family 17
[    0.240795] EXT4-fs (vda1): mounted filesystem with ordered data mode. Opts: (null)
[    0.240859] VFS: Mounted root (ext4 filesystem) on device 254:1.
[    0.241001] devtmpfs: mounted
[    0.241341] Freeing unused kernel memory: 448K
+ mount -t proc - /proc
+ mount -t sysfs - /sys
+ mount -t debugfs - /sys/kernel/debug/
+ [ -e /dev/sdb1 ]
+ [ -e /dev/sdb ]
+ [ -e /dev/vdb1 ]
top - 00:29:29 up 29 min,  1 user,  load average: 0.00, 0.00, 0.00
Tasks:  41 total,   1 running,  13 sleeping,   0 stopped,   0 zombie
%Cpu(s):  0.0 us,  0.0 sy,  0.0 ni,100.0 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
KiB Mem :  2051156 total,  2032748 free,     7464 used,    10944 buff/cache
KiB Swap:        0 total,        0 free,        0 used.  2004432 avail Mem 

  PID USER      PR  NI    VIRT    RES    SHR S %CPU %MEM     TIME+ COMMAND      
    1 root      20   0    5436   2500   2040 S  0.0  0.1   0:00.04 login        
    2 root      20   0       0      0      0 S  0.0  0.0   0:00.00 kthreadd     
    3 root       0 -20       0      0      0 I  0.0  0.0   0:00.00 rcu_gp       
    4 root       0 -20       0      0      0 I  0.0  0.0   0:00.00 rcu_par_gp   
    6 root       0 -20       0      0      0 I  0.0  0.0   0:00.00 kworker/0:0+ 
    7 root      20   0       0      0      0 I  0.0  0.0   0:00.00 kworker/u2:+ 
    8 root       0 -20       0      0      0 I  0.0  0.0   0:00.00 mm_percpu_wq 
    9 root      20   0       0      0      0 S  0.0  0.0   0:00.00 ksoftirqd/0  
   10 root      20   0       0      0      0 I  0.0  0.0   0:00.00 rcu_preempt  
   11 root      20   0       0      0      0 I  0.0  0.0   0:00.00 rcu_sched    
   12 root      20   0       0      0      0 I  0.0  0.0   0:00.00 rcu_bh       
   13 root      rt   0       0      0      0 S  0.0  0.0   0:00.00 migration/0  
   14 root      20   0       0      0      0 S  0.0  0.0   0:00.00 cpuhp/0      
   15 root      20   0       0      0      0 S  0.0  0.0   0:00.00 kdevtmpfs    
   16 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcu_tasks_k+ 
   17 root      20   0       0      0      0 I  0.0  0.0   0:00.00 kworker/u2:+ 
   45 root      20   0       0      0      0 I  0.0  0.0   0:00.00 kworker/0:1+ 

root@aarch64-gem5:~# exit                            
logout
[ 1809.732578] Kernel panic - not syncing: Attempted to kill init! exitcode=0x00000000
[ 1809.732578] 
[ 1809.732640] CPU: 0 PID: 1 Comm: login Not tainted 4.18.0+ #1
[ 1809.732673] Hardware name: V2P-CA15 (DT)
[ 1809.732698] Call trace:
[ 1809.732723]  dump_backtrace+0x0/0x1c0
[ 1809.732747]  show_stack+0x14/0x20
[ 1809.732772]  dump_stack+0x8c/0xac
[ 1809.732795]  panic+0x130/0x288
[ 1809.732816]  complete_and_exit+0x0/0x20
[ 1809.732841]  do_group_exit+0x38/0xa0
[ 1809.732864]  __wake_up_parent+0x0/0x28
[ 1809.732889]  el0_svc_naked+0x30/0x34
[ 1809.732914] Kernel Offset: disabled
[ 1809.732937] CPU features: 0x21c06292
[ 1809.732960] Memory Limit: 2048 MB
[ 1809.732984] ---[ end Kernel panic - not syncing: Attempted to kill init! exitcode=0x00000000
[ 1809.732984]  ]--


