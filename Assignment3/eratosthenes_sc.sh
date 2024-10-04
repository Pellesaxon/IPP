#!/bin/bash

Max=(1000 100000 10000000)
Thread_values=(1 2 4 8 16 32)

for M in "${Max[@]}"; do
    for T in "${Thread_values[@]}"; do
        echo "Max=$M and Threads=$T"
        ./eratosthenes_omp $M $T 
    done
done