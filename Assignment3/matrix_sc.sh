#!/bin/bash

Dimentions=(64 256 1024)
Thread_values=(1 2 4 8 16 32)

for N in "${Dimentions[@]}"; do
    for T in "${Thread_values[@]}"; do
        echo "Dimentions=$N x $N, Threads=$T"
        ./matrix $N $T
    done
done