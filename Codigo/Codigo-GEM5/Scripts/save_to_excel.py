import pandas as pd
from collections import defaultdict

# Inicializar un diccionario para almacenar los valores por nombre
data = defaultdict(list)

# Leer el archivo de texto
with open('/home/fluctlights/Escritorio/Repos/tfm/Codigo/Codigo-GEM5/Base/stats_base_benchmark.txt', 'r') as file:
    for line in file:
        # Omitir las cabeceras si no siguen el formato nombre valor
        parts = line.strip().split()
        name, value = parts
        if len(parts) > 1:
            data[name].append(value[1])

# Convertir el diccionario a un DataFrame
df = pd.DataFrame(dict([(k, pd.Series(v)) for k, v in data.items()]))

# Añadir una fila vacía
df.loc[-1] = [None] * len(df.columns)
df.index = df.index + 1
df = df.sort_index()

# Guardar el DataFrame en un archivo Excel sin la columna de índice
df.to_excel('/home/fluctlights/Escritorio/Repos/tfm/Codigo/Codigo-GEM5/Base/resultados.xlsx', index=False)