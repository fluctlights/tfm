import glob
import pandas as pd
import os

benchmark_names = ["DHRYSTONE", "WHETSTONE", "CALC-PI", "CALC-PRIME"]
directory = "../Codigo-PAPI/CSV/RPi4/PruebasFull/Benchmarks/"
sort_key = "name"

for benchmark_name in benchmark_names:
    merged_df = pd.DataFrame()
    file_paths = glob.glob(f"{directory}{benchmark_name}*.csv")
    sorted_filepaths = sorted(file_paths, key=lambda x: x if sort_key is None else (getattr(os.stat(x), sort_key) if hasattr(os.stat(x), sort_key) else x))
    
    for file_path in sorted_filepaths:
        df = pd.read_csv(file_path)
        merged_df = pd.concat([merged_df, df], axis=1, join='outer')

    # Save the merged DataFrame to a new Excel file
    merged_df.to_csv(f"{directory}{benchmark_name}_merged.csv", index=False)

