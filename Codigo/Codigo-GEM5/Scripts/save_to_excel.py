import pandas as pd
import sys
from collections import defaultdict

# Inicializar un diccionario para almacenar los valores por nombre
data = defaultdict(list)
benchmark_type = sys.argv[1]
benchmark_file = ''
benchmark_spreadsheet = ''

if benchmark_type == 'base':
    benchmark_file = "/home/fluctlights/Escritorio/Repos/tfm/Codigo/Codigo-GEM5/Base/base_stats.txt"
    benchmark_spreadsheet = "/home/fluctlights/Escritorio/Repos/tfm/Codigo/Codigo-GEM5/Base/resultados_base.xlsx"
else:
    benchmark_file = "/home/fluctlights/Escritorio/Repos/tfm/Codigo/Codigo-GEM5/Benchmarks/benchmark_stats.txt"
    benchmark_spreadsheet = "/home/fluctlights/Escritorio/Repos/tfm/Codigo/Codigo-GEM5/Benchmarks/resultados_benchmark.xlsx"

try:
    # Leer el archivo de texto
    with open(benchmark_file, 'r') as file:
        for line in file:
            # Omitir las cabeceras si no siguen el formato nombre valor
            parts = line.strip().split()
            if len(parts) != 2:
                if len(parts) > 1:
                    if not isinstance(parts[1], str):
                        data[parts[0]].append(parts[1])
            
            else:
                name, value = parts
                data[name].append(value)

except Exception as e:
    print(e)

# Convertir el diccionario a un DataFrame
df = pd.DataFrame(dict([(k, pd.Series(v)) for k, v in data.items()]))

# Añadir una fila vacía
df.loc[-1] = [None] * len(df.columns)
df.index = df.index + 1
df = df.sort_index()

# Guardar el DataFrame en un archivo Excel sin la columna de indice
df.to_excel(benchmark_spreadsheet, index=False)

