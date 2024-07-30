#!/bin/bash

#######################
# CONFIGURANDO CPUSET #
#######################

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


########################
# DESPLEGUE DE PRUEBAS #
########################

if [ -z "$2" ]; then
    echo "ERROR! USAGE: ./deploy --repetitions <value>"

else
	sudo sh -c 'echo -1 >/proc/sys/kernel/perf_event_paranoid'
	mkdir -p ./CSV
	rm benchmarks > /dev/null 2>&1

	items=("1" "2" "3" "4" "5" "6" "7" "8" "9")
	pmu_events_sets=("PMU_SET_0" "PMU_SET_1" "PMU_SET_2" "PMU_SET_3")
	n_repetitions=$2

	for item in "${items[@]}"
	do
		if [[ $item == "1" ]]; then
			echo "Ejecutando benchmark SoloMain"

			for pmu_events in "${pmu_events_sets[@]}"
			do
				gcc -O0 -D$pmu_events -DREPETITIONS=$n_repetitions benchmarks_menu.c -o benchmarks -lpapi -lm > /dev/null 2>&1
				sudo cgexec -g cpuset:$CPUSET_NAME ./benchmarks -b $item
			done
		fi

		if [[ $item == "2" ]]; then
			echo "Ejecutando benchmark Suma de enteros"

			for pmu_events in "${pmu_events_sets[@]}"
			do
				gcc -O0 -D$pmu_events -DREPETITIONS=$n_repetitions benchmarks_menu.c -o benchmarks -lpapi -lm > /dev/null 2>&1
				sudo cgexec -g cpuset:$CPUSET_NAME ./benchmarks -b $item
			done
		fi
		
		if [[ $item == "3" ]]; then
			echo "Ejecutando benchmark Suma de flotantes"

			for pmu_events in "${pmu_events_sets[@]}"
			do
				gcc -O0 -D$pmu_events -DREPETITIONS=$n_repetitions benchmarks_menu.c -o benchmarks -lpapi -lm > /dev/null 2>&1
				sudo cgexec -g cpuset:$CPUSET_NAME ./benchmarks -b $item
			done
		fi

		if [[ $item == "4" ]]; then
			echo "Ejecutando benchmark Multiplicacion de enteros (factorial)"

			for pmu_events in "${pmu_events_sets[@]}"
			do
				gcc -O0 -D$pmu_events -DREPETITIONS=$n_repetitions benchmarks_menu.c -o benchmarks -lpapi -lm > /dev/null 2>&1
				sudo cgexec -g cpuset:$CPUSET_NAME ./benchmarks -b $item
			done
		fi

		if [[ $item == "5" ]]; then
			echo "Ejecutando benchmark Multiplicacion de flotantes (factorial)"

			for pmu_events in "${pmu_events_sets[@]}"
			do
				gcc -O0 -D$pmu_events -DREPETITIONS=$n_repetitions benchmarks_menu.c -o benchmarks -lpapi -lm > /dev/null 2>&1
				sudo cgexec -g cpuset:$CPUSET_NAME ./benchmarks -b $item
			done
		fi

		if [[ $item == "6" ]]; then
			echo "Ejecutando benchmark Division de enteros"

			for pmu_events in "${pmu_events_sets[@]}"
			do
				gcc -O0 -D$pmu_events -DREPETITIONS=$n_repetitions benchmarks_menu.c -o benchmarks -lpapi -lm > /dev/null 2>&1
				sudo cgexec -g cpuset:$CPUSET_NAME ./benchmarks -b $item
			done
		fi

		if [[ $item == "7" ]]; then
			echo "Ejecutando benchmark Division de flotantes"

			for pmu_events in "${pmu_events_sets[@]}"
			do
				gcc -O0 -D$pmu_events -DREPETITIONS=$n_repetitions benchmarks_menu.c -o benchmarks -lpapi -lm > /dev/null 2>&1
				sudo cgexec -g cpuset:$CPUSET_NAME ./benchmarks -b $item
			done
		fi

		if [[ $item == "8" ]]; then
			echo "Ejecutando benchmark Acceso de vector (vector swap)"

			for pmu_events in "${pmu_events_sets[@]}"
			do
				gcc -O0 -D$pmu_events -DREPETITIONS=$n_repetitions benchmarks_menu.c -o benchmarks -lpapi -lm > /dev/null 2>&1
				sudo cgexec -g cpuset:$CPUSET_NAME ./benchmarks -b $item
			done
		fi

		if [[ $item == "9" ]]; then
			echo "Ejecutando benchmark Copia de vector"

			for pmu_events in "${pmu_events_sets[@]}"
			do
				gcc -O0 -D$pmu_events -DREPETITIONS=$n_repetitions benchmarks_menu.c -o benchmarks -lpapi -lm > /dev/null 2>&1
				sudo cgexec -g cpuset:$CPUSET_NAME ./benchmarks -b $item
			done
		fi

	done
fi