#!/bin/bash

if [ -z "$2" ]; then
    echo "ERROR! USAGE: ./deploy --repetitions <value>"

else
	sudo sh -c 'echo -1 >/proc/sys/kernel/perf_event_paranoid'
	rm benchmarks_deploy > /dev/null 2>&1

	items=("D" "W" "p" "P")
	sizes_dhrystone=("60000" "120000" "240000" "480000" "960000")
	sizes_whetstone=("3000" "6000" "12000" "24000" "48000")
	sizes_calcpi=("300000" "600000" "1200000" "2400000" "4800000")
	sizes_calcprime=("3000" "6000" "12000" "24000" "48000")
	n_repetitions=$2
	
	gcc -O0 -static -DREPETITIONS=$n_repetitions benchmarks_deploy.c -o benchmarks_deploy -lm > /dev/null 2>&1

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
				
				for i in {1..5}; do
					./benchmarks_deploy -b $item -s $size
				done
				sleep 1
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

				for i in {1..5}; do
					./benchmarks_deploy -b $item -s $size
				done
				sleep 1
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

				for i in {1..5}; do
					./benchmarks_deploy -b $item -s $size
				done
				sleep 1
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

				for i in {1..5}; do
					./benchmarks_deploy -b $item -s $size
				done
				sleep 1
			done
		fi
	done
fi
