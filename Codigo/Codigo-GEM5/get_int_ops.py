import csv

def parse_report(filename):

    conteo = 0
    val = 0
    
    with open(filename, 'r') as f:
        for line in f:
            parts = line.split()
            #print(parts)

            mylist = ["l2.overallAccesses::total"]
            # Check for instruction type line
        
            if len(parts) >= 1:
            
                if any(item in parts[0] for item in mylist):

                    val = int(parts[1])
                    strin = f"{val},"
                    print(strin)



# Replace 'path/to/report.txt' with the actual path to your report file
report_data = parse_report('/home/fluctlights/Escritorio/Repos/tfm/gem5/pruebas/stats.txt')
