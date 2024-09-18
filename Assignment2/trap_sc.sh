#!/bin/bash

Trapezoid_values=(10000 10000000 1000000000)
Thread_values=(1 2 4 8 16 32)

for TR in "${Trapezoid_values[@]}"; do
    for TH in "${Thread_values[@]}"; do
        echo "Running program with Trapezoids=$TR and Threads=$TH"
        ./trapeze $TR $TH 
    done
done
