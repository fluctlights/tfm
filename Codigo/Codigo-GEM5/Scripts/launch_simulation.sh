#!/bin/bash

# Current Variables for Gem5 Trials!
export M5_PATH=/home/fluctlights/Escritorio/Repos/tfm/gem5/Kernels
export GEM5_HOME=/home/fluctlights/Escritorio/Repos/tfm/gem5
export GEM5_PATH=/home/fluctlights/Escritorio/Repos/tfm/gem5
export CODE_PATH=/home/fluctlights/Escritorio/Repos/tfm/Codigo/Codigo-GEM5

CHECKPOINT=""
OPTION=""

# Handle Ctrl+C
handle_interrupt() {
    echo "SIMULATION DONE!!!!"
    trap - SIGINT #unset the interruption
    exit
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
        --script $CODE_PATH/Scripts/make_checkpoint.sh

    # Waits for Ctrl+C to continue

else
    
    while [[ "$OPTION" != "1" && "$OPTION" != "2" ]]; do
        echo "What kind of simulations want to do?"
        echo "[1] Basic benchmarks"
        echo "[2] Synthetic benchmarks"
        read OPTION
        if [[ "$OPTION" != "1" && "$OPTION" != "2" ]]; then
            echo "ERROR! Choose either 1 or 2."
            sleep 1
        fi
    done

    if [[ $OPTION == "1" ]]; then
		$GEM5_PATH/build/ARM/gem5.opt -d $GEM5_PATH/pruebas \
            --stats-file=text://stats.txt?spaces=False \
            $GEM5_PATH/configs/example/arm/starter_fs.py \
            --cpu="o3" --num-cores=4 \
            --disk-image=$M5_PATH/disks/ubuntu-18.04-extended.img \
            --root-device=/dev/vda1 --mem-type DDR4_2400_8x8 --mem-size 4GB \
            --restore $GEM5_PATH/pruebas/cpt.$2/ --power-models \
            --pw-model-number 5
	
    else
        $GEM5_PATH/build/ARM/gem5.opt \
            -d $GEM5_PATH/pruebas \
            --stats-file=text://stats.txt?spaces=False \
            $GEM5_PATH/configs/example/arm/starter_fs.py \
            --cpu="o3" --num-cores=4 \
            --disk-image=$M5_PATH/disks/ubuntu-18.04-extended.img \
            --root-device=/dev/vda1 --mem-type DDR4_2400_8x8 --mem-size 4GB \
            --restore $GEM5_PATH/pruebas/cpt.$2/ --power-models \
            --pw-model-number 5
    fi

fi


