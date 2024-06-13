#!/bin/bash

if [ -z "$2" ]; then
    echo "ERROR! USAGE: ./deploy --repetitions <value>"

else
	sudo sh -c 'echo -1 >/proc/sys/kernel/perf_event_paranoid'
	mkdir -p ./CSV
	rm benchmarks_test > /dev/null 2>&1

	items=("D" "W" "p" "P")
	pmu_events_sets=("PMU_SET_0" "PMU_SET_1" "PMU_SET_2" "PMU_SET_3")
	sizes_dhrystone=("60000" "120000" "240000" "480000" "960000")
	sizes_whetstone=("3000" "6000" "12000" "24000" "48000")
	sizes_calcpi=("300000" "600000" "1200000" "2400000" "4800000")
	sizes_calcprime=("3000" "6000" "12000" "24000" "48000")
	n_repetitions=$2

	for item in "${items[@]}"
	do
		if [[ $item == "D" ]]; then
			echo "Ejecutando benchmark Dhrystone"

			for pmu_events in "${pmu_events_sets[@]}"
			do
				gcc -O0 -D$pmu_events -DREPETITIONS=$n_repetitions benchmarks_test.c -o benchmarks_test -lpapi -lm > /dev/null 2>&1

				for size_dhrystone in "${sizes_dhrystone[@]}"
				do
					./benchmarks_test -b $item -s $size_dhrystone
				done
			done
		fi

		if [[ $item == "W" ]]; then
			echo "Ejecutando benchmark Whetstone"

			for pmu_events in "${pmu_events_sets[@]}"
			do
				gcc -O0 -D$pmu_events -DREPETITIONS=$n_repetitions benchmarks_test.c -o benchmarks_test -lpapi -lm > /dev/null 2>&1

				for size_whetstone in "${sizes_whetstone[@]}"
				do
					./benchmarks_test -b $item -s $size_whetstone
				done
			done
		fi

		if [[ $item == "p" ]]; then
			echo "Ejecutando benchmark Calculo de Pi"

			for pmu_events in "${pmu_events_sets[@]}"
			do
				gcc -O0 -D$pmu_events -DREPETITIONS=$n_repetitions benchmarks_test.c -o benchmarks_test -lpapi -lm > /dev/null 2>&1

				for size_calcpi in "${sizes_calcpi[@]}"
				do
					./benchmarks_test -b $item -s $size_calcpi
				done
			done
		fi

		if [[ $item == "P" ]]; then
			echo "Ejecutando benchmark Calculo de primos"

			for pmu_events in "${pmu_events_sets[@]}"
			do
				gcc -O0 -D$pmu_events -DREPETITIONS=$n_repetitions benchmarks_test.c -o benchmarks_test -lpapi -lm > /dev/null 2>&1

				for size_calcprime in "${sizes_calcprime[@]}"
				do
					./benchmarks_test -b $item -s $size_calcprime
				done
			done
		fi
	done
fi
