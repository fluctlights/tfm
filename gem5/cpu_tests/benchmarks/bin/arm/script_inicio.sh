#!/bin/bash

#/opt/glibc/lib/libc.so.6 /home/prueba
#/opt/glibc/lib/libc.so.6 --library-path /opt/glibc /home/prueba
LD_LIBRARY_PATH=/opt/glibc/lib /home/prueba
