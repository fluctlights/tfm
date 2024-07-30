#!/bin/bash

export M5_PATH=/home/fluctlights/Escritorio/Repos/tfm/gem5/Kernels

sudo mount -t auto -o loop,offset=65536 $M5_PATH/disks/ubuntu-18.04-extended.img /mnt/gem5-img/
sudo mount --bind /dev /mnt/gem5-img/dev
sudo mount --bind /proc /mnt/gem5-img/proc
sudo mount --bind /sys /mnt/gem5-img/sys
sudo chroot /mnt/gem5-img /bin/bash
