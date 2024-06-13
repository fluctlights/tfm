#!/bin/bash

if [ -z "$2" ]; then
    echo "ERROR! USAGE: ./deploy --repetitions <value>"

else
	sudo sh -c 'echo -1 >/proc/sys/kernel/perf_event_paranoid'
	rm benchmarks_deploy > /dev/null 2>&1

	items=("D" "W" "p" "P")
	sizes_dhrystone=("30000" "80000" "400000" "200000" "10000000")
	sizes_whetstone=("300" "5500" "40000" "65000" "200000")
	sizes_calcpi=("300000" "905000" "4000000" "25000000" "100000000")
	sizes_calcprime=("3000" "9500" "40000" "250000" "1000000")
	n_repetitions=$2

	for item in "${items[@]}"
	do
		if [[ $item == "D" ]]; then
			echo "Ejecutando benchmark Dhrystone"
			gcc -O0 -DREPETITIONS=$n_repetitions benchmarks_deploy.c -o benchmarks_deploy -lm > /dev/null 2>&1

			for size_dhrystone in "${sizes_dhrystone[@]}"
			do
				./benchmarks_deploy -b $item -s $size_dhrystone
			done
		fi

		if [[ $item == "W" ]]; then
			echo "Ejecutando benchmark Whetstone"
			gcc -O0 -DREPETITIONS=$n_repetitions benchmarks_deploy.c -o benchmarks_deploy -lm > /dev/null 2>&1

			for size_whetstone in "${sizes_whetstone[@]}"
			do
				./benchmarks_deploy -b $item -s $size_whetstone
			done
		fi

		if [[ $item == "p" ]]; then
			echo "Ejecutando benchmark Calculo de Pi"
			gcc -O0 -DREPETITIONS=$n_repetitions benchmarks_deploy.c -o benchmarks_deploy -lm > /dev/null 2>&1

			for size_calcpi in "${sizes_calcpi[@]}"
			do
				./benchmarks_deploy -b $item -s $size_calcpi
			done
		fi

		if [[ $item == "P" ]]; then
			echo "Ejecutando benchmark Calculo de primos"
			gcc -O0 -DREPETITIONS=$n_repetitions benchmarks_deploy.c -o benchmarks_deploy -lm > /dev/null 2>&1

			for size_calcprime in "${sizes_calcprime[@]}"
			do
				./benchmarks_deploy -b $item -s $size_calcprime
			done
		fi
	done
fi
