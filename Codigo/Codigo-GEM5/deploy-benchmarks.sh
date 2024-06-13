#!/bin/bash

cd /home/Codigo-GEM5

items=("D" "W" "p" "P")

# FACTOR 2 PARA CONSEGUIR LINEALIDAD!!
sizes_dhrystone=("60000" "120000" "240000" "480000" "960000")
sizes_whetstone=("3000" "6000" "12000" "24000" "48000")
sizes_calcpi=("300000" "600000" "1200000" "2400000" "4800000")
sizes_calcprime=("3000" "6000" "12000" "24000" "48000")
n_repetitions=6

for item in "${items[@]}"
do
	if [[ $item == "D" ]]; then
		# Ejecutando benchmark Dhrystone
		for size_dhrystone in "${sizes_dhrystone[@]}"
		do
			./benchmarks -b $item -s $size_dhrystone
		done
	fi

	if [[ $item == "W" ]]; then
		# Ejecutando benchmark Whetstone
		for size_whetstone in "${sizes_whetstone[@]}"
		do
			./benchmarks -b $item -s $size_whetstone
		done
	fi

	if [[ $item == "p" ]]; then
		# Ejecutando benchmark Calculo de Pi
		for size_calcpi in "${sizes_calcpi[@]}"
		do
			./benchmarks -b $item -s $size_calcpi
		done
	fi

	if [[ $item == "P" ]]; then
		# Ejecutando benchmark Calculo de primos
		for size_calcprime in "${sizes_calcprime[@]}"
		do
			./benchmarks -b $item -s $size_calcprime
		done
	fi
done
