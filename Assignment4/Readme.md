# Authors

Oskar Perers and Lukas Bygdell Malmstig 
October 2024

# Requirements

This solution runs on C++11

# How to run

To compile the programs use <code>make all</code> or <code>make programname.exe</code>

The different programs can then be run by typing <code>make run_\<programname></code>

<code>eratosthenes_mpi.exe</code> is run with <code>make run_eratosthenes_single</code> which will run the program with a differantiating number of processes on a single node or <code>make run_eratosthenes_all</code> which will run the program with a differantiating number of processes on all three nodes.

<code>eratosthenes_bc.exe</code> is run with <code>make run_eratosthenes_bc</code> which will run the program with a differantiating number of processes on all three nodes.
