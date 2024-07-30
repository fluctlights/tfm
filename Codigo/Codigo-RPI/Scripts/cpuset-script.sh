#!/bin/bash

# Nombre del cpuset
CPUS=0
MEMS=0
CPUSET_NAME="my_cpuset"

# Crear y montar el sistema de archivos cpuset si no está ya montado
if ! mount | grep -q cpuset; then
    sudo mkdir -p /dev/cpuset
    sudo mount -t cpuset cpuset /dev/cpuset
fi

# Crear el cpuset
sudo mkdir -p /dev/cpuset/$CPUSET_NAME

# Asignar CPUs y memoria
echo $CPUS | sudo tee /dev/cpuset/$CPUSET_NAME/cpus
echo $MEMS | sudo tee /dev/cpuset/$CPUSET_NAME/mems

# Ejecutar el comando en el cpuset
sudo cgexec -g cpuset:$CPUSET_NAME "$@"