#!/bin/bash

Dimentions=(64 1024 4096)
Time_steps=(1000 2000)
Thread_values=(1 2 4 8 16 32)

for N in "${Dimentions[@]}"; do
    for Time in "${Time_steps[@]}"; do
        for T in "${Thread_values[@]}"; do
            echo "Dimentions=$N x $N, Timesteps = $Time, Threads=$T"
            ./gol $N $Time $T
        done
    done
done