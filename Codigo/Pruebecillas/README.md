# Notas PAPI

PAPI (Peformance API) es una poderosa herramienta para medir el rendimiento de un sistema. En el contexto de este trabajo, PAPI estará orientado a su utilización a la hobenchmarks. Para esto, se apoya en el acceso a eventos a nivel hardware. PAPI se basa en varias herramientas y tecnologías subyacentes que varían según la arquitectura del sistema en el que se está ejecutando, como toda siute de perf y perf_event, así como los módulos libpfm3 y libpfm4. 

Hay dos posibles formas de utilizar PAPI, con la interfaz de alto nivel y la de bajo nivel.

## Interfaz de alto nivel

La interfaz de alto nivel proporciona un fácil acceso a diferentes métricas, por medio de programas python que están disponibles directamente en el terminal.


Además, la interfaz de alto nivel permite una recogida de métricas muy interesante a nivel de benchmark. En este documento se realizarán ejecuciones del benchmark Dhrystone, pero es extrapolable a cualquier otro.

Para poder obtener los datos es necesario definir en el shell las variables de entorno de PAPI
Por defecto no es necesario pero los resultados pueden ser demasiado generales

```sh
export PAPI_EVENTS="perf::TASK-CLOCK,PAPI_TOT_INS,PAPI_TOT_CYC,PAPI_FP_INS"
export PAPI_OUTPUT_DIRECTORY="dhrystone-hl-stats/measurement"
```

Con esto obtenemos un fichero en dhrystone-hl-stats/measurement. Como ejemplo,se muestra una ejecución del benchmark Dhrystone. El resultado es el siguiente:

```sh
{
  "cpu in mhz":"1500",
  "threads":[
    {
      "id":"11067",
      "regions":[
        {
          "computation":{
            "region_count":"1",
            "cycles":"18788826",
            "perf::TASK-CLOCK":"346705407",
            "PAPI_TOT_INS":"637003822",
            "PAPI_TOT_CYC":"437893091",
            "PAPI_FP_INS":"0"
          }
        }
      ]
    }
  ]
}
```

En este escenario no hay operaciones de punto flotante. Esto es por la propia naturaleza del benchmark Dhrystone.

El resultado en JSON se puede mejorar y obtener métricas derivadas ejecutando el siguiente comando:

```sh
papi_hl_output_writer.py --source ./dhrystone-hl-stats/measurement/papi_hl_output
```

Obteniéndose el siguiente resultado:

```sh
{
    "ranks": [
        {
            "id": "1VGh60",
            "threads": [
                {
                    "id": "11067",
                    "regions":
                        {
                            "computation": {
                                "Region count": 1,
                                "Real time in s": 0.01,
                                "CPU time in s": 0.35,
                                "IPC": 1.45,
                                "MFLIPS/s": 0.0
                        }  
                }
            ]
        }
    ]
}

```

## Interfaz de bajo nivel

En este escenario en teoria los resultados son más precisos, reduciendo el número de instrucciones tenidas en cuenta.  Por el momento no he sido capaz de mejorar los resultados obtenidos frente a la interfaz de alto nivel. No estoy del todo seguro si merece la pena teniendo en cuenta los resultados que se pueden obtener con la versión de alto nivel

