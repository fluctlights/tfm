#!/bin/bash

cd /home/Codigo-GEM5/Base

items=("1" "2" "3" "4" "5" "6" "7" "8" "9")

for item in "${items[@]}"
do
	if [[ $item == "1" ]]; then
		./benchmarks -b $item
	fi

	if [[ $item == "2" ]]; then
		./benchmarks -b $item
	fi
	
	if [[ $item == "3" ]]; then
		./benchmarks -b $item
	fi

	if [[ $item == "4" ]]; then
		./benchmarks -b $item
	fi

	if [[ $item == "5" ]]; then
		./benchmarks -b $item
	fi

	if [[ $item == "6" ]]; then
		./benchmarks -b $item
	fi

	if [[ $item == "7" ]]; then
		./benchmarks -b $item
	fi

	if [[ $item == "8" ]]; then
		./benchmarks -b $item
	fi

	if [[ $item == "9" ]]; then
		./benchmarks -b $item
	fi

done