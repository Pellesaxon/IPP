# Authors

Oskar Perers and Lukas Bygdell Malmstig 
October 2024

# Requirements

This solution runs on C++11 or any modern version of C.

# How to run

To compile the programs use <code>make all</code> or <code>make programname.exe</code>

The different programs can then be run by typing <code>./programname.exe</code> in your teminal or by using <code>make run_\<programname></code>

<code>eratosthenes_omp.exe</code> providing MAX which is the max number we will check if it is a prime number and T which is the number of threads as arguments. It is also run with <code>make run_eratosthenes</code> which will run a script with a number of combinations for these two commandline arguments for <code>eratosthenes_omp.exe</code>.

<code>gol.exe</code> can be run manually by providing N which is the size of the game board, Time which is the number of timesteps to run and T which is the number of threads as arguments. It can also be run via <code>make run_gol</code> which will run a script with a number of combinations for these three commandline arguments. 

<code>gol_print.exe</code> can be run manually by providing N which is the size of the game board, Time which is the number of timesteps to run and T which is the number of threads as arguments. It can also be run via <code>make run_gol</code> which will run the program with N = 64, Time = 300 and T = 4. This version will print out a gif of the game if FFmpeg is installed.

<code>matrix.exe</code> can be run manually by providing N which is the dimension of the matrices multiplied and T which is the number of threads as arguments. It is also run with <code>make run_matrix</code> which will run a script with a number of combinations for these two commandline arguments for <code>matrix.exe</code>.

<code>gaus_row.exe</code> and <code>gaus_col.exe</code> can be run manually by providing N which is the dimension of the matrices used and T which is the number of threads as arguments. It is also run with <code>make run_gaus</code> which will run both programs with a number of combinations for these two commandline arguments.