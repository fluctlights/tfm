#!/bin/bash

############################
# DECLARACION DE VARIABLES #
############################

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
    "---- OPERATIONS ISSUED BY EACH CPU THREAD ----" # estadisticas de las instrucciones realizadas
)

############################
# DECLARACION DE FUNCIONES #
############################

save_to_excel() 
{
    python_script="
import pandas as pd
from collections import defaultdict

# Inicializar un diccionario para almacenar los valores por nombre
data = defaultdict(list)

# Leer el archivo de texto
with open('reduced_stats.txt', 'r') as file:
    for line in file:
        # Omitir las cabeceras si no siguen el formato nombre valor
        parts = line.strip().split()
        if len(parts) != 2:
            continue
        name, value = parts
        data[name].append(value)

# Convertir el diccionario a un DataFrame
df = pd.DataFrame(dict([(k, pd.Series(v)) for k, v in data.items()]))

# Añadir una fila vacía
df.loc[-1] = [None] * len(df.columns)
df.index = df.index + 1
df = df.sort_index()

# Guardar el DataFrame en un archivo Excel sin la columna de índice
df.to_excel('salida.xlsx', index=False)
"
    echo "$python_script" | python
}

print_first_lines()
{
    echo "" >> $output_file
    echo "##########################################################################" >> $output_file
    echo "" >> $output_file
    
    # Marcar nueva ejecucion de benchmark
    if (( num_executions >= 0 && num_executions <= 4 )); then
        echo "------------------------------------------------" >> $output_file
        echo "EXECUTION $num_executions - DHRYSTONE BENCHMARK" >> $output_file
        echo "------------------------------------------------" >> $output_file
    elif (( num_executions >= 5 && num_executions <= 9 )); then
        echo "------------------------------------------------" >> $output_file
        echo "EXECUTION $num_executions - WHETSTONE BENCHMARK" >> $output_file
        echo "------------------------------------------------" >> $output_file
    elif (( num_executions >= 10 && num_executions <= 14 )); then
        echo "----------------------------------------------" >> $output_file
        echo "EXECUTION $num_executions - CALC-PI BENCHMARK" >> $output_file
        echo "----------------------------------------------" >> $output_file
    elif (( num_executions >= 15 && num_executions <= 29 )); then
        echo "--------------------------------------------------" >> $output_file
        echo "EXECUTION $num_executions - CALC-PRIMES BENCHMARK" >> $output_file
        echo "--------------------------------------------------" >> $output_file
    else
        echo "BENCHMARKS EJECUTADOS!!"
        exit 0
    fi

    # Imprimiendo los atributos iniciales, no pertenecientes a CPU concretas
    echo "" >> $output_file
    echo "---------- GLOBAL ATTRIBUTES ----------" >> $output_file
    echo "" >> $output_file
}


main()
{
    file_to_monitor="$GEM5_PATH/pruebas/stats.txt"
    output_file="reduced_stats.txt"

    prev_size=$(stat --format="%s" "$file_to_monitor")
    sleep_time=15
    current_size=-1
    num_lines=6107 # lineas que ocupa un dump de datos
    num_executions=0 # numero de ejecuciones realizadas
    stats_desc_pointer=0 # posicion del array de descripciones

    while true; do
        # Obtiene el tamaño actual del archivo usando `stat`
        current_size=$(stat --format="%s" "$file_to_monitor")

        # Verifica si el tamaño del archivo ha cambiado y si el archivo tiene contenido
        if [ "$current_size" -ne "$prev_size" ] && [ "$current_size" -gt 0 ]; then

            sleep $sleep_time

            stats_desc_pointer=0 # posicion del array de descripciones

            # Leer las últimas líneas del archivo
            new_lines=$(tail -n "$num_lines" "$file_to_monitor")

            print_first_lines

            # Imprimiendo los atributos iniciales, no pertenecientes a CPU concretas
            echo "" >> $output_file
            echo "---------- GLOBAL ATTRIBUTES ----------" >> $output_file
            echo "" >> $output_file


            # Recorre la matriz de atributos generales
            for pattern in "${general_attrs[@]}"; do
                
                # Buscar cada patrón en las nuevas líneas
                matches=$(echo "$new_lines" | grep -E "$pattern")
                echo "$matches" >> $output_file
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
                stats_desc_pointer=$((stats_desc_pointer + 1)) # Nuevo descriptor

            done

            # Actualiza el tamaño anterior del archivo
            prev_size=$current_size
            num_executions=$((num_executions + 1)) # Nuevo descriptor

            save_to_excel # Guardamos un excel de lo que aparece en el archivo

        fi

        sleep $sleep_time
    done
}

########
# TODO #
########

main