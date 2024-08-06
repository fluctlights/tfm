#!/bin/bash

cd /home/Codigo-GEM5
rm benchmarks_deploy_gem5 > /dev/null 2>&1

items=("D" "W" "p" "P")

# FACTOR 2 PARA CONSEGUIR LINEALIDAD!!
sizes_dhrystone=("30000" "60000" "120000" "240000" "480000")
sizes_whetstone=("3000" "6000" "12000" "24000" "48000")
sizes_calcpi=("300000" "600000" "1200000" "2400000" "4800000")
sizes_calcprime=("3000" "6000" "12000" "24000" "48000")
n_repetitions=6

gcc -O0 -DREPETITIONS=$n_repetitions benchmarks_deploy_gem5.c -o benchmarks_deploy_gem5 -lm > /dev/null 2>&1

for item in "${items[@]}"
do
	if [[ $item == "D" ]]; then
		for size_dhrystone in "${sizes_dhrystone[@]}"
		do
			./benchmarks_deploy_gem5 -b $item -s $size_dhrystone
		done
	fi

	if [[ $item == "W" ]]; then
		for size_whetstone in "${sizes_whetstone[@]}"
		do
			./benchmarks_deploy_gem5 -b $item -s $size_whetstone
		done
	fi

	if [[ $item == "p" ]]; then
		for size_calcpi in "${sizes_calcpi[@]}"
		do
			./benchmarks_deploy_gem5 -b $item -s $size_calcpi
		done
	fi

	if [[ $item == "P" ]]; then
		for size_calcprime in "${sizes_calcprime[@]}"
		do
			./benchmarks_deploy_gem5 -b $item -s $size_calcprime
		done
	fi
done
