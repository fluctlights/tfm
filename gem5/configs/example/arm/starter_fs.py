# Copyright (c) 2016-2017, 2020, 2022 Arm Limited
# All rights reserved.
#
# The license below extends only to copyright in the software and shall
# not be construed as granting a license to any other intellectual
# property including but not limited to intellectual property relating
# to a hardware implementation of the functionality of the software
# licensed hereunder.  You may use the software subject to the license
# terms below provided that you ensure that this notice is replicated
# unmodified and in its entirety in all distributions of the software,
# modified or unmodified, in source code or in binary form.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met: redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer;
# redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution;
# neither the name of the copyright holders nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

"""This script is the full system example script from the ARM
Research Starter Kit on System Modeling. More information can be found
at: http://www.arm.com/ResearchEnablement/SystemModeling
"""

import argparse
from ast import arguments
import os

import m5
from m5.objects import *
from m5.options import *
from m5.util import addToPath

m5.util.addToPath("../..")

import devices
from common import (
    MemConfig,
    ObjectList,
    SysPaths,
)
from common.cores.arm import (
    HPI,
    O3_ARM_v7a,
)

from m5.objects import MathExprPowerModel
from m5.objects import PowerModel

default_kernel = "vmlinux.arm64"
default_disk = "linaro-minimal-aarch64.img"
default_root_device = "/dev/vda1"

clock_freq = ((1/(666/1000000000000))/1000000)
voltage_sq = (0.8688*0.8688)

# CPU configurations. Each tuple must be ordered as : (cpu_class,
# l1_icache_class, l1_dcache_class, l2_Cache_class). Any of
# the cache class may be 'None' if the particular cache is not present.
cpu_types = {
    "atomic": (AtomicSimpleCPU, None, None, None),
    "minor": (MinorCPU, devices.L1I, devices.L1D, devices.L2),
    "hpi": (HPI.HPI, HPI.HPI_ICache, HPI.HPI_DCache, HPI.HPI_L2),
    "o3": (
        O3_ARM_v7a.O3_ARM_v7a_3,
        O3_ARM_v7a.O3_ARM_v7a_ICache,
        O3_ARM_v7a.O3_ARM_v7a_DCache,
        O3_ARM_v7a.O3_ARM_v7aL2
    ),
}

class CpuPowerOn(MathExprPowerModel):
    def __init__(self, cpu_path, args, **kwargs):
        super(CpuPowerOn, self).__init__(**kwargs)

        # Result are in Watt (power of each core).
        
        if(args.pw_model_number == 1): 
            self.dyn = (
                "(((({}.numCycles*system.clk_domain.clock)/(simSeconds*1000000000000000000)) * 1501.5 * (0.8688*0.8688) * 0.000000000606992538845)* 1000000000000)".format(cpu_path)
            )

        if(args.pw_model_number == 2):
            self.dyn = (
                "((({}.numCycles * 0.000000000606992538845) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000)))"
                " + "
                "(({}.dcache.overallAccesses * 0.00000000023263372317) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000))))".format(cpu_path, cpu_path)
            )
        
        # elif(args.pw_model_number == 3):
        #     self.dyn = (
        #         "((({}.numCycles * 0.000000000606992538845) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000)))"
        #         " + "
        #         "(({}.dcache.overallAccesses * 0.00000000023263372317) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000)))"
        #         " + "
        #         "(({}.executeStats0.numInsts * 0.000000000543933973638) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000)))"
        #         " - "
        #         "((({}.commit.committedInstType_0::IntAlu * 0.000000000543933973638) + ({}.commit.committedInstType_0::IntMult * 0.000000000543933973638) + ({}.commit.committedInstType_0::IntDiv * 0.000000000543933973638)) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000))))".format(cpu_path, cpu_path, cpu_path, cpu_path, cpu_path, cpu_path)
        #     )

        # elif(args.pw_model_number == 4):
        #     self.dyn = (
        #         "((({}.numCycles * 0.000000000606992538845) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000)))"
        #         " + "
        #         "(({}.dcache.overallAccesses * 0.00000000023263372317) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000)))"
        #         #" + "
        #         #"(({}.executeStats0.numInsts * 0.000000000543933973638) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000)))"
        #         #" - "
        #         #"((({}.executeStats0.commitStats0.committedInstType::IntAlu * 0.000000000543933973638) + ({}.commitStats0.committedInstType::IntMult * 0.000000000543933973638) + ({}.commitStats0.committedInstType::IntDiv * 0.000000000543933973638)) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000)))"
        #         " + "
        #         "(({}.dcache.WriteReq.misses * 0.0000000479625288372) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000))))".format(cpu_path, cpu_path, cpu_path, cpu_path, cpu_path, cpu_path, cpu_path)
        #     )

        elif(args.pw_model_number == 5):
            self.dyn = (
                "((({}.numCycles * 0.000000000606992538845) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000)))"
                " + "
                "(({}.dcache.overallAccesses * 0.00000000023263372317) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000)))"
                " + "
                "(({}.executeStats0.numInsts * 0.000000000543933973638) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000)))"
                " - "
                "((({}.executeStats0.commitStats0.committedInstType::IntAlu * 0.000000000543933973638) + ({}.commitStats0.committedInstType::IntMult * 0.000000000543933973638) + ({}.commitStats0.committedInstType::IntDiv * 0.000000000543933973638)) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000)))"
                " + "
                "(({}.dcache.WriteReq.misses::total * 0.0000000479625288372) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000)))"
                " + "
                "(({}.dcache.ReadReq.accesses::total * 0.000000000841332534886) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000)))"
                " + "
                "((({}.executeStats0.commitStats0.committedInstType::IntAlu * 0.000000000244859350364) + ({}.commitStats0.committedInstType::IntMult * 0.000000000244859350364) + ({}.commitStats0.committedInstType::IntDiv * 0.000000000244859350364)) * ((system.clk_domain.clock * 1501.5 * (0.8688*0.8688) * 1000000000000)/(simSeconds*1000000000000000000))))".format(cpu_path, cpu_path, cpu_path, cpu_path, cpu_path, cpu_path, cpu_path, cpu_path, cpu_path, cpu_path, cpu_path)
            )

        else: # default model
            self.dyn = (
                "1*simSeconds"
            )

        # Static energy is always the same
        self.st = (
            "((1 * (-681.604059986)) + (((1/(system.clk_domain.clock/1000000000000))/1000000) * 0.117551170367) + (system.voltage_domain.voltage * 2277.16890778) + (((1/(system.clk_domain.clock/1000000000000))/1000000) * system.voltage_domain.voltage * (-0.491846201277)) + ((system.voltage_domain.voltage * system.voltage_domain.voltage) * (-2528.1574686)) + (((1/(system.clk_domain.clock/1000000000000))/1000000) * (system.voltage_domain.voltage*system.voltage_domain.voltage) * 0.645456768269) + ((system.voltage_domain.voltage * system.voltage_domain.voltage * system.voltage_domain.voltage) * 932.937276293) + (((1/(system.clk_domain.clock/1000000000000))/1000000) * (system.voltage_domain.voltage*system.voltage_domain.voltage*system.voltage_domain.voltage) * (-0.271180478671))*(-1))"
        )

class CpuPowerOff(MathExprPowerModel):
    dyn = "0"
    st = "0"

class CpuPowerModel(PowerModel):
    def __init__(self, cpu_path, args, **kwargs):
        super(CpuPowerModel, self).__init__(**kwargs)
        self.pm = [
            CpuPowerOn(cpu_path, args),  # ON
            CpuPowerOff(),  # CLK_GATED
            CpuPowerOff(),  # SRAM_RETENTION
            CpuPowerOff(),  # OFF
        ]

class L2PowerOn(MathExprPowerModel):
    def __init__(self, l2_path, **kwargs):
        super(L2PowerOn, self).__init__(**kwargs)
        
        # Example to report l2 Cache overallAccesses
        # The estimated power is converted to Watt and will vary based on the size of the cache
        # Data extracted from Soton University and ARM papers.
        self.dyn = (
            "((((system.cpu_cluster.l2.overallAccesses*system.clk_domain.clock)/(simSeconds*1000000000000000000)) * 1501.5 * (0.8688*0.8688) * 0.00000000572830963981)* 1000000000000)"
        )
        self.st = "((0.8688 * 3)/10)" # provided by gem5 documentation

class L2PowerOff(MathExprPowerModel):
    dyn = "0"
    st = "0"

class L2PowerModel(PowerModel):
    def __init__(self, l2_path, **kwargs):
        super(L2PowerModel, self).__init__(**kwargs)
        # Choose a power model for every power state
        self.pm = [
            L2PowerOn(l2_path),  # ON
            L2PowerOff(),  # CLK_GATED
            L2PowerOff(),  # SRAM_RETENTION
            L2PowerOff(),  # OFF
        ]


def create_cow_image(name):
    """Helper function to create a Copy-on-Write disk image"""
    image = CowDiskImage()
    image.child.image_file = SysPaths.disk(name)

    return image


def create(args):
    """Create and configure the system object."""

    if args.script and not os.path.isfile(args.script):
        print(f"Error: Bootscript {args.script} does not exist")
        sys.exit(1)

    cpu_class = cpu_types[args.cpu][0]
    mem_mode = cpu_class.memory_mode()
    # Only simulate caches when using a timing CPU (e.g., the HPI model)
    want_caches = True if mem_mode == "timing" else False

    system = devices.SimpleSystem(
        want_caches,
        args.mem_size,
        mem_mode=mem_mode,
        workload=ArmFsLinux(object_file=SysPaths.binary(args.kernel)),
        readfile=args.script,
    )

    MemConfig.config_mem(args, system)

    # Add the PCI devices we need for this system. The base system
    # doesn't have any PCI devices by default since they are assumed
    # to be added by the configuration scripts needing them.
    system.pci_devices = [
        # Create a VirtIO block device for the system's boot
        # disk. Attach the disk image using gem5's Copy-on-Write
        # functionality to avoid writing changes to the stored copy of
        # the disk image.
        PciVirtIO(vio=VirtIOBlock(image=create_cow_image(args.disk_image)))
    ]

    # Attach the PCI devices to the system. The helper method in the
    # system assigns a unique PCI bus ID to each of the devices and
    # connects them to the IO bus.
    for dev in system.pci_devices:
        system.attach_pci(dev)

    # Wire up the system's memory system
    system.connect()

    # Add CPU clusters to the system
    
    system.cpu_cluster = [
        devices.ArmCpuCluster(
            system,
            args.num_cores,
            "1.5GHz", # 1GHz
            "0.8688V", # 1V
            *cpu_types[args.cpu],
            tarmac_gen=args.tarmac_gen,
            tarmac_dest=args.tarmac_dest,
        )
    ]
    
    if args.use_dvfs:
        system.dvfs_handler.domains = [system.cpu_cluster[0].clk_domain]
        system.dvfs_handler.enable = True
        

    # Create a cache hierarchy for the cluster. We are assuming that
    # clusters have core-private L1 caches and an L2 that's shared
    # within the cluster.
    system.addCaches(want_caches, last_cache_level=2)

    # Setup gem5's minimal Linux boot loader.
    system.realview.setupBootLoader(system, SysPaths.binary)

    if args.dtb:
        system.workload.dtb_filename = args.dtb
    else:
        # No DTB specified: autogenerate DTB
        system.workload.dtb_filename = os.path.join(
            m5.options.outdir, "system.dtb"
        )
        system.generateDtb(system.workload.dtb_filename)

    if args.initrd:
        system.workload.initrd_filename = args.initrd

    # Linux boot command flags
    kernel_cmd = [
        # Tell Linux to use the simulated serial port as a console
        "console=ttyAMA0",
        # Hard-code timi
        "lpj=19988480",
        # Disable address space randomisation to get a consistent
        # memory layout.
        "norandmaps",
        # Tell Linux where to find the root disk image.
        f"root={args.root_device}",
        # Mount the root disk read-write by default.
        "rw",
        # Tell Linux about the amount of physical memory present.
        f"mem={args.mem_size}",
    ]
    system.workload.command_line = " ".join(kernel_cmd)

    if args.with_pmu:
        for cluster in system.cpu_cluster:
            interrupt_numbers = [args.pmu_ppi_number] * len(cluster)
            cluster.addPMUs(interrupt_numbers)

    return system


def run(args):
    cptdir = m5.options.outdir
    if args.checkpoint:
        print(f"Checkpoint directory: {cptdir}")

    while True:
        event = m5.simulate()
        exit_msg = event.getCause()
        if exit_msg == "checkpoint":
            print("Dropping checkpoint at tick %d" % m5.curTick())
            cpt_dir = os.path.join(m5.options.outdir, "cpt.%d" % m5.curTick())
            m5.checkpoint(os.path.join(cpt_dir))
            print("Checkpoint done.")

        elif exit_msg == "exit":
            print("Execution ended on tick %d\n" % m5.curTick())
        
        else:
            print(f"{exit_msg} ({event.getCode()}) @ {m5.curTick()}")
            break


def arm_ppi_arg(int_num: int) -> int:
    """Argparse argument parser for valid Arm PPI numbers."""
    # PPIs (1056 <= int_num <= 1119) are not yet supported by gem5
    int_num = int(int_num)
    if 16 <= int_num <= 31:
        return int_num
    raise ValueError(f"{int_num} is not a valid Arm PPI number")


def main():
    parser = argparse.ArgumentParser()

    parser.add_argument(
        "--dtb", type=str, default=None, help="DTB file to load"
    )
    parser.add_argument(
        "--kernel", type=str, default=default_kernel, help="Linux kernel"
    )
    parser.add_argument(
        "--initrd",
        type=str,
        default=None,
        help="initrd/initramfs file to load",
    )
    parser.add_argument(
        "--disk-image",
        type=str,
        default=default_disk,
        help="Disk to instantiate",
    )
    parser.add_argument(
        "--root-device",
        type=str,
        default=default_root_device,
        help=f"OS device name for root partition (default: {default_root_device})",
    )
    parser.add_argument(
        "--script", type=str, default="", help="Linux bootscript"
    )
    parser.add_argument(
        "--cpu",
        type=str,
        choices=list(cpu_types.keys()),
        default="atomic",
        help="CPU model to use",
    )
    parser.add_argument("--cpu-freq", type=str, default="1.5GHz")
    parser.add_argument(
        "--num-cores", type=int, default=1, help="Number of CPU cores"
    )
    parser.add_argument(
        "--mem-type",
        default="DDR3_1600_8x8",
        choices=ObjectList.mem_list.get_names(),
        help="type of memory to use",
    )
    parser.add_argument(
        "--mem-channels", type=int, default=1, help="number of memory channels"
    )
    parser.add_argument(
        "--mem-ranks",
        type=int,
        default=None,
        help="number of memory ranks per channel",
    )
    parser.add_argument(
        "--mem-size",
        action="store",
        type=str,
        default="2GB",
        help="Specify the physical memory size",
    )
    parser.add_argument(
        "--tarmac-gen",
        action="store_true",
        help="Write a Tarmac trace.",
    )
    parser.add_argument(
        "--tarmac-dest",
        choices=TarmacDump.vals,
        default="stdoutput",
        help="Destination for the Tarmac trace output. [Default: stdoutput]",
    )
    parser.add_argument(
        "--with-pmu",
        action="store_true",
        help="Add a PMU to each core in the cluster.",
    )
    parser.add_argument(
        "--pmu-ppi-number",
        type=arm_ppi_arg,
        default=23,
        help="The number of the PPI to use to connect each PMU to its core. "
        "Must be an integer and a valid PPI number (16 <= int_num <= 31).",
    )
    parser.add_argument(
        "--power-models", 
        action="store_true",
        help="Add power models to the simulated system. "
        "Requires using the 'timing' CPU.",
    )
    parser.add_argument(
        "--use-dvfs", 
        action="store_true",
        help="Use DVFS schema on the simulation",
    )
    parser.add_argument("--checkpoint", action="store_true")
    parser.add_argument("--restore", type=str, default=None)

    parser.add_argument(
        "--stats-file",
        metavar="FILE",
        default="stats.txt",
        help="Sets the output file for statistics [Default: %default]",
    )

    parser.add_argument(
        "--pw-model-number",
        type=int,
        default=1,
        help="The power model to use in the simulation. A higher value represents more attributes taken into account"
        "The model chosen will estimate power with more (higher value) or less (lower value) attributes",
    )

    args = parser.parse_args()

    root = Root(full_system=True)
    root.system = create(args)

    if args.power_models:
        for cpu in root.system.descendants():
            if not isinstance(cpu, m5.objects.BaseCPU):
                continue

            cpu.power_state.default_state = "ON"
            cpu.power_model = CpuPowerModel(cpu.path(), args)


        # Example power model for the L2 Cache
        for l2 in root.system.cpu_cluster.descendants():
            if not isinstance(l2, m5.objects.Cache):
                continue

            l2.power_state.default_state = "ON"
            l2.power_model = L2PowerModel(l2.path())

    if args.restore is not None:
        m5.instantiate(args.restore)
    else:
        m5.instantiate()

# esta instruccion hace que haya todo el rato stats y se queda enorme el fichero
# m5.stats.periodicStatDump(m5.ticks.fromSeconds(0.1e-3))
    run(args)

if __name__ == "__m5_main__":
    main()