#!/bin/bash

if [ -z "$2" ]; then
    echo "ERROR! USAGE: ./deploy --repetitions <value>"

else
	sudo sh -c 'echo -1 >/proc/sys/kernel/perf_event_paranoid'
	rm benchmarks_deploy > /dev/null 2>&1

	items=("D" "W" "p" "P")
	
	# VALORES DE LOS BENCHMARK ORIGINALES MULTIPLICADOS POR:

	sizes_dhrystone=("96000000") # X 100
	sizes_whetstone=("480000") # X 10
	sizes_calcpi=("960000000") # X 200
	sizes_calcprime=("2400000") # X 50
	n_repetitions=$2
	
	aarch64-linux-gnu-gcc -O0 -static -DREPETITIONS=$n_repetitions benchmarks_deploy.c -o benchmarks_deploy -lm > /dev/null 2>&1

	for item in "${items[@]}"
	do
		if [[ $item == "D" ]]; then
			for size in "${sizes_dhrystone[@]}" 
			do
				echo "Ejecutando benchmark Dhrystone"
				echo ""
				echo "LISTO? [yes]"
				read decision
				echo ""
				./benchmarks_deploy -b $item -s $size
			done
		fi

		if [[ $item == "W" ]]; then
			for size in "${sizes_whetstone[@]}" 
			do
				echo "Ejecutando benchmark Whetstone"
				echo ""
				echo "LISTO? [yes]"
				read decision
				echo ""
				./benchmarks_deploy -b $item -s $size
			done
		fi

		if [[ $item == "p" ]]; then
			for size in "${sizes_calcpi[@]}" 
			do
				echo "Ejecutando benchmark Calculo de Pi"
				echo ""
				echo "LISTO? [yes]"
				read decision
				echo ""
				./benchmarks_deploy -b $item -s $size
			done
		fi

		if [[ $item == "P" ]]; then
			for size in "${sizes_calcprime[@]}"
			do
				echo "Ejecutando benchmark Calculo de primos"
				echo ""
				echo "LISTO? [yes]"
				read decision
				echo ""
				./benchmarks_deploy -b $item -s $size
			done
		fi
	done
fi
