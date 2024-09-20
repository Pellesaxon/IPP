#!/bin/bash

Max_=(10000 10000000 1000000000)
Thread_values=(1 2 4 8 16 32)

for M in "${Max[@]}"; do
    for T in "${Thread_values[@]}"; do
        echo "Max=$M and Threads=$T"
        ./eratosthenes_sc $M $T 
    done
done

echo "\n___________________________________\n New test with random\n ___________________________________\n"

for M in "${Max[@]}"; do
    for T in "${Thread_values[@]}"; do
        echo "Max=$M and Threads=$T"
        ./eratosthenes_random_sc $M $T 
    done
done