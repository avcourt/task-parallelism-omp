#!/bin/bash

# Runs $num_tests num_runs times with increasing thread values
# 2, 4, .8, ...


thresh=32     	# threshold at which sort reverts to insertion
arr_size=$((2**30)) # num of integer elements to sort
num_tests=5        # num of different tests (threads = [ 1, 2, 4, ... 2^ num_tests-1])
num_runs=5         	# number of runs/thread count
start=1				# start with this many threads

num_threads=${start}       
type=merge_sect		# program name

echo "num threads = ${num_threads}" >> mergesort_results/${type}.txt && wait
for (( i = 0; i < ${num_tests} * ${num_runs}; i++ ))
do
    if ! ((i % ${num_runs})) && ((i > 0)); then
    	num_threads=$((num_threads * 2))
	 	echo "num threads = ${num_threads}" >> mergesort_results/${type}.txt && wait
    fi
       ./${type} ${arr_size} ${thresh} ${num_threads} >> mergesort_results/${type}.txt && wait
done


