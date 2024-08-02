#!/bin/bash

#######################################
# DECLARACION DE VARIABLES DE ENTORNO #
#######################################

export M5_PATH=/home/fluctlights/Escritorio/Repos/tfm/gem5/Kernels
export GEM5_HOME=/home/fluctlights/Escritorio/Repos/tfm/gem5
export GEM5_PATH=/home/fluctlights/Escritorio/Repos/tfm/gem5
export CODE_PATH=/home/fluctlights/Escritorio/Repos/tfm/Codigo/Codigo-GEM5

############################
# DECLARACION DE VARIABLES #
############################

simulation_lines=0 # lineas que ocupa una simulacion
stats_file="$GEM5_PATH/pruebas/stats.txt"
output_file=""
python_script=""
total_executions=0
declare -a line_counts # tamaño de las lineas entre begin y end en cada ejecucion

if [[ "$1" == "benchmarks" ]]; then
    output_file="$CODE_PATH/Benchmarks/benchmark_stats.txt"
    python_script="$CODE_PATH/Scripts/save_to_excel.py benchmarks"
    total_executions=60
    
elif [[ "$1" == "base" ]]; then
    output_file="$CODE_PATH/Base/base_stats.txt"
    python_script="$CODE_PATH/Scripts/save_to_excel.py base"
    total_executions=27
fi

num_executions=0 # numero de ejecuciones realizadas

declare -a general_attrs=(
    "simFreq" 
    "simTicks" 
    "finalTick" 
    "simInsts" 
    "simOps" 
    "simSeconds"
    "hostSeconds"
    "system.clk_domain.clock"
)

declare -a patterns=(
    "system.cpu_cluster.cpus[0-3].power_model.dynamicPower"
    "system.cpu_cluster.cpus[0-3].power_model.staticPower"
    "system.cpu_cluster.cpus[0-3].numCycles"
    "system.cpu_cluster.cpus[0-3].cpi"
    "system.cpu_cluster.cpus[0-3].ipc"
    "system.cpu_cluster.cpus[0-3].commit.committedInstType_0\:*" # tipos de instrucciones realizadas
    "system.cpu_cluster.cpus[0-3].commitStats0.numOps" # sumatorio de todos los tipos de instrucciones realizadas (thread level)
    "system.cpu_cluster.cpus[0-3].commitStats0.numInsts" # valor mas pequeño y al parecer sin sentido alguno, pero se deja (thread level)
    "system.cpu_cluster.cpus[0-3].executeStats0\.*" # (thread level)
    "system.cpu_cluster.cpus[0-3].fetch\.*"
    "system.cpu_cluster.cpus[0-3].decode\.*"
    "system.cpu_cluster.cpus[0-3].statIssuedInstType_0\:*" # estadisticas de las instrucciones realizadas
    "system.cpu_cluster.cpus[0-3].dcache\.*" # level 1 data cache info
    "system.cpu_cluster.l2\.*" # level 2 data cache info
)

declare -a patterns_description=(
    "---- DYNAMIC POWER ----"
    "---- STATIC POWER ----"
    "---- NUMBER OF CYCLES ----"
    "---- CYCLES PER INSTRUCTION ----"
    "---- INSTRUCTIONS PER CYCLE ----"
    "---- TYPES OF INSTRUCTIONS COMMITTED ----" # tipos de instrucciones realizadas
    "---- OPERATIONS DONE BY EACH CPU THREAD ----" # sumatorio de todos los tipos de instrucciones realizadas (thread level)
    "---- INSTRUCTIONS DONE BY EACH CPU THREAD ----" # valor mas pequeño y al parecer sin sentido alguno, pero se deja (thread level)
    "---- OPERATIONS EXECUTED BY EACH CPU THREAD ----" # (thread level)
    "---- OPERATIONS FETCHED BY EACH CPU THREAD ----"
    "---- OPERATIONS DECODED BY EACH CPU THREAD ----"
    "---- INSTRUCTIONS ISSUED BY EACH CPU THREAD ----" # estadisticas de las instrucciones realizadas
    "---- LEVEL 1 DATA CACHE INFORMATION BY EACH CPU THREAD ----"
    "---- LEVEL 2 DATA CACHE ACCESSES ----"
)

############################
# DECLARACION DE FUNCIONES #
############################

print_base_first_lines()
{
    echo "" >> $output_file
    echo "##########################################################################" >> $output_file
    echo "" >> $output_file
    
    # Marcar nueva ejecucion de benchmark
    if (( num_executions >= 0 && num_executions <= 2 )); then
        echo "------------------------------------------------" >> $output_file
        echo "EXECUTION $num_executions - SOLOMAIN BENCHMARK" >> $output_file
        echo "------------------------------------------------" >> $output_file
    elif (( num_executions >= 3 && num_executions <= 5 )); then
        echo "------------------------------------------------" >> $output_file
        echo "EXECUTION $num_executions - ALU-SUMS BENCHMARK" >> $output_file
        echo "------------------------------------------------" >> $output_file
    elif (( num_executions >= 6 && num_executions <= 8 )); then
        echo "-----------------------------------------------" >> $output_file
        echo "EXECUTION $num_executions - FPU-SUMS BENCHMARK" >> $output_file
        echo "------------------------------------------------" >> $output_file
    elif (( num_executions >= 9 && num_executions <= 11 )); then
        echo "-----------------------------------------------" >> $output_file
        echo "EXECUTION $num_executions - ALU-MULT BENCHMARK" >> $output_file
        echo "-----------------------------------------------" >> $output_file
    elif (( num_executions >= 12 && num_executions <= 14 )); then
        echo "-----------------------------------------------" >> $output_file
        echo "EXECUTION $num_executions - FPU-MULT BENCHMARK" >> $output_file
        echo "-----------------------------------------------" >> $output_file
    elif (( num_executions >= 15 && num_executions <= 17 )); then
        echo "----------------------------------------------" >> $output_file
        echo "EXECUTION $num_executions - ALU-DIV BENCHMARK" >> $output_file
        echo "----------------------------------------------" >> $output_file
    elif (( num_executions >= 18 && num_executions <= 20 )); then
        echo "----------------------------------------------" >> $output_file
        echo "EXECUTION $num_executions - FPU-DIV BENCHMARK" >> $output_file
        echo "----------------------------------------------" >> $output_file
    elif (( num_executions >= 21 && num_executions <= 23 )); then
        echo "-------------------------------------------------" >> $output_file
        echo "EXECUTION $num_executions - MEM-ACCESS BENCHMARK" >> $output_file
        echo "-------------------------------------------------" >> $output_file
    elif (( num_executions >= 24 && num_executions <= 26 )); then
        echo "-----------------------------------------------" >> $output_file
        echo "EXECUTION $num_executions - MEM-COPY BENCHMARK" >> $output_file
        echo "-----------------------------------------------" >> $output_file
    fi

    # Imprimiendo los atributos iniciales, no pertenecientes a CPU concretas
    echo "" >> $output_file
    echo "---------- GLOBAL ATTRIBUTES ----------" >> $output_file
    echo "" >> $output_file
}

print_benchmark_first_lines()
{
    echo "" >> $output_file
    echo "##########################################################################" >> $output_file
    echo "" >> $output_file
    
    # Marcar nueva ejecucion de benchmark
    if (( num_executions >= 0 && num_executions <= 14 )); then
        echo "------------------------------------------------" >> $output_file
        echo "EXECUTION $num_executions - DHRYSTONE BENCHMARK" >> $output_file
        echo "------------------------------------------------" >> $output_file
    elif (( num_executions >= 15 && num_executions <= 29 )); then
        echo "------------------------------------------------" >> $output_file
        echo "EXECUTION $num_executions - WHETSTONE BENCHMARK" >> $output_file
        echo "------------------------------------------------" >> $output_file
    elif (( num_executions >= 30 && num_executions <= 44 )); then
        echo "----------------------------------------------" >> $output_file
        echo "EXECUTION $num_executions - CALC-PI BENCHMARK" >> $output_file
        echo "----------------------------------------------" >> $output_file
    elif (( num_executions >= 45 && num_executions <= 59 )); then
        echo "--------------------------------------------------" >> $output_file
        echo "EXECUTION $num_executions - CALC-PRIMES BENCHMARK" >> $output_file
        echo "--------------------------------------------------" >> $output_file
    fi

    # Imprimiendo los atributos iniciales, no pertenecientes a CPU concretas
    echo "" >> $output_file
    echo "---------- GLOBAL ATTRIBUTES ----------" >> $output_file
    echo "" >> $output_file
}

read_simulation_lines()
{
    # Obtiene el tamaño actual del archivo usando `stat`
    current_size=$(stat --format="%s" "$stats_file")

    # Comprobar que el fichero tiene simulaciones realizadas previamente
    if [ "$current_size" -eq 0 ]; then
        echo "File is empty! Try some simulation first!"
        exit 1
    fi
    
    # Flag para saber si estamos dentro de un bloque de simulacion
    in=0

    input_file="$stats_file"

    # Leer fichero linea a linea desde Begin hasta encontrar End
    # Asi sacamos el numero de lineas de cada bloque de simulacion
    while IFS= read -r line; do

        # Check for the start
        if [[ "$line" == "---------- Begin Simulation Statistics ----------" ]]; then
            in=1
            sim_lines=$((sim_lines + 1))

        # Check for the end
        elif [[ "$line" == "---------- End Simulation Statistics   ----------" ]]; then
            in=2
            sim_lines=$((sim_lines + 1))
        fi

        if (( in == 2 )); then # end found
            sim_lines=$((sim_lines - 1))
            line_counts+=("$sim_lines")
            sim_lines=0
            in=0
        else
            sim_lines=$((sim_lines + 1)) # continue counting lines
        fi
    done < "$input_file"
}

main()
{
    # Leer fichero linea a linea desde Begin hasta encontrar End
    # Asi sacamos el numero de lineas de cada bloque de simulacion

    start_line=1
    input_file="$stats_file"
    index=0

    while true; do

        # Todas las ejecuciones realizadas
        if (( num_executions == total_executions )); then
            echo "Estadisticas guardadas!"
            exit 0
        fi
        
        simulation_lines=${line_counts[index]}
        endline=$((start_line + simulation_lines - 1))
        #new_lines=""
        #new_lines=$(head -n "$endline" "$input_file" | tail -n "$simulation_lines")
        new_lines=$(sed -n "${start_line},${endline}p" "$input_file")
        sleep 1

        if [[ "$1" -eq "base" ]]; then
            print_base_first_lines
        else
            print_benchmark_first_lines
        fi

        # Recorre la matriz de atributos generales
        for pattern in "${general_attrs[@]}"; do
            # Buscar cada patrón en las nuevas líneas
            matches=$(echo "$new_lines" | grep -E "$pattern")
            echo "$matches" >> $output_file
            sleep 1
        done

        # Recorre la matriz de patrones de busqueda
        for pattern in "${patterns[@]}"; do
            
            # Buscar cada patrón en las nuevas líneas
            matches=$(echo "$new_lines" | grep -E "$pattern")

            # Imprimir descritor
            echo "" >> $output_file
            echo "${patterns_description[stats_desc_pointer]}" >> $output_file
            echo "" >> $output_file

            # Muestreo por CPU de cada patrón
            for cpu_num in {0..3}; do
                
                filtered_matches=$(echo "$matches" | grep "cpus$cpu_num")
            
                if [[ -n "$filtered_matches" ]]; then 
                    echo "$filtered_matches" >> $output_file
                    echo "" >> $output_file # Línea vacía para separar los resultados por CPU
                fi
            done
            
            echo "" >> $output_file # Línea vacía para separar los resultados por patrón

        done

        num_executions=$((num_executions + 1)) # Nuevo descriptor
        index=$((index + 1)) # Nuevo descriptor
        start_line=$((start_line + simulation_lines))
        new_lines=
        python3 $python_script # Guardamos un excel de lo que aparece en el archivo

    done
}

########
# TODO #
########

read_simulation_lines
main