#!/bin/bash

# Current Variables for Gem5 Trials!
export M5_PATH=/home/fluctlights/Escritorio/Repos/tfm/gem5/Kernels
export GEM5_HOME=/home/fluctlights/Escritorio/Repos/tfm/gem5
export GEM5_PATH=/home/fluctlights/Escritorio/Repos/tfm/gem5

CHECKPOINT=""

# Handle Ctrl+C
handle_interrupt() {
    echo "SIMULATION DONE!!!!"
    trap - SIGINT #unset the interruption
    echo "Now please enter the ticks of checkpoint:"
    read CHECKPOINT
}

if [ -z "$2" ]; then

    # Set up the interruption
    trap handle_interrupt SIGINT
    echo "Launching new simulation!"

    $GEM5_PATH/build/ARM/gem5.opt \
        -d $GEM5_PATH/pruebas \
        --stats-file=text://stats.txt?spaces=False \
        $GEM5_PATH/configs/example/arm/starter_fs.py \
        --cpu="atomic" --num-cores=4 \
        --disk-image=$M5_PATH/disks/ubuntu-18.04-extended.img \
        --root-device=/dev/vda1 --mem-type DDR4_2400_8x8 --mem-size 4GB \
        --script make_checkpoint.sh

    # Waits for Ctrl+C to continue

    $GEM5_PATH/build/ARM/gem5.opt \
        -d $GEM5_PATH/pruebas \
        --stats-file=text://stats.txt?spaces=False \
        $GEM5_PATH/configs/example/arm/starter_fs.py \
        --cpu="o3" --num-cores=4 \
        --disk-image=$M5_PATH/disks/ubuntu-18.04-extended.img \
        --root-device=/dev/vda1 --mem-type DDR4_2400_8x8 --mem-size 4GB \
        --restore $GEM5_PATH/pruebas/cpt.$CHECKPOINT/ --power-models \
        --pw-model-number 1
else
    $GEM5_PATH/build/ARM/gem5.opt \
        -d $GEM5_PATH/pruebas \
        --stats-file=text://stats.txt?spaces=False \
        $GEM5_PATH/configs/example/arm/starter_fs.py \
        --cpu="o3" --num-cores=4 \
        --disk-image=$M5_PATH/disks/ubuntu-18.04-extended.img \
        --root-device=/dev/vda1 --mem-type DDR4_2400_8x8 --mem-size 4GB \
        --restore $GEM5_PATH/pruebas/cpt.$2/ --power-models \
        --pw-model-number 3
fi

