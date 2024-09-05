#!/bin/bash

T_values=(1 2 4 8 16 32)
N_values=(1 2 4 8 16 32)

for T in "${T_values[@]}"; do
    for N in "${N_values[@]}"; do
        echo "Running program with T=$T and N=$N"
        ./performance $T $N  
    done
done
