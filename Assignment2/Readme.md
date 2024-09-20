# Authors

Oskar Perers and Lukas Bygdell Malmstig 
September 2024

# Requirements

This solution runs on C++11

# How to run

To compile the programs use <code>make all</code>

The different programs can then be run by typing <code>./programname.exe</code> in your teminal or by using <code>make run_\<programname></code>

<code>trapeze.exe</code> can be run manualy by providing N which is the number of trapezoids to divide the calculation into and T which is the number of threads as argumnets. But it can also be run with <code>make run_trapeze</code> which will run a script with a number of combinations for these two comandline arguments.

<code>dtrapeze.exe</code> can be run manualy by providing N which is the number of trapezoids to divide the calculation into, T which is the number of threads as argumnets and the optional Bucket_scaling modifire which can be used to tune how large the buckets will be. It can also be run via <code>make run_dtrapeze</code> which will run a script with a number of combinations for these two comandline arguments.

<code>eratosthenes.exe</code> can be run manualy by providing MAX which is the max number we will check if it is a prime number and T which is the number of threads as argumnets. It is also run with <code>make run_eratosthenes</code> which will run a script with a number of combinations for these two comandline arguments for both <code>eratosthenes.exe</code> and <code>eratosthenes_random.exe</code>.

<code>eratosthenes_random.exe</code> can be run manualy by providing MAX which is the max number we will check if it is a prime number and T which is the number of threads as argumnets. It is also run with <code>make run_eratosthenes</code> which will run a script with a number of combinations for these two comandline arguments for both <code>eratosthenes.exe</code> and <code>eratosthenes_random.exe</code>.