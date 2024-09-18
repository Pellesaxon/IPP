#!/bin/bash

Trapezoid_values=(10000 10000000 1000000000)
Thread_values=(1 2 4 8 16 32)
Dynamic_bucket_scaling=(1000 10000 1000000) # How big each bucket of work should be

for TR in "${Trapezoid_values[@]}"; do
    for TH in "${Thread_values[@]}"; do
        for DBS in "${Thread_values[@]}"; do
            echo "Running program with Trapezoids=$TR, Threads=$TH and Bucket_scaling=$DBS"  
            ./dtrapeze $TR $TH $DBS
        done
    done
done
