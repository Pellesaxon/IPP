# Authors

Oskar Perers and Lukas Bygdell Malmstig 
September 2024

# Requirements

This solution runs on C++11
All except benchmark which runs on C++20 as it uses a modern feature

# How to run

To compile the programs use <code>make all</code>

The different programs can then be run by typing <code>./programname.exe</code> in your teminal or by using <code>make run_\<programname></code>

<code>trapeze.exe</code> can be run manually by providing N which is the number of trapezoids to divide the calculation into and T which is the number of threads as arguments. But it can also be run with <code>make run_trapeze</code> which will run a script with a number of combinations for these two commandline arguments.

<code>dtrapeze.exe</code> can be run manually by providing N which is the number of trapezoids to divide the calculation into, T which is the number of threads as arguments and the optional Bucket_scaling modifier which can be used to tune how large the buckets will be. It can also be run via <code>make run_dtrapeze</code> which will run a script with a number of combinations for these two commandline arguments.

<code>eratosthenes.exe</code> can be run manually by providing MAX which is the max number we will check if it is a prime number and T which is the number of threads as arguments. It is also run with <code>make run_eratosthenes</code> which will run a script with a number of combinations for these two commandline arguments for both <code>eratosthenes.exe</code> and <code>eratosthenes_random.exe</code>.

<code>eratosthenes_random.exe</code> can be run manually by providing MAX which is the max number we will check if it is a prime number and T which is the number of threads as arguments. It is also run with <code>make run_eratosthenes</code> which will run a script with a number of combinations for these two commandline arguments for both <code>eratosthenes.exe</code> and <code>eratosthenes_random.exe</code>.

<code>eratosthenes_random.exe</code> can be run manually by providing MAX which is the max number we will check if it is a prime number and T which is the number of threads as arguments. It is also run with <code>make run_eratosthenes</code> which will run a script with a number of combinations for these two commandline arguments for both <code>eratosthenes.exe</code> and <code>eratosthenes_random.exe</code>.

<code>bench.exe</code> can be run manually by providing the T which is the number of threads as arguments. It is also run with <code>make run_bench</code> which will run the benchmark for all implemented solutions with 4 threads.