#!/bin/bash

# Define the values for T and N
T_values=(1 2 4 8 16 32)
N_values=(1 2 4 8 16 32)

# Loop over each combination of T and N
for T in "${T_values[@]}"; do
    for N in "${N_values[@]}"; do
        echo "Running program with T=$T and N=$N"
        ./your_program $T $N  # Replace "your_program" with the actual name of your executable
    done
done
