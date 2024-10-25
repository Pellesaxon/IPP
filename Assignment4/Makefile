C++flags = g++ -std=c++11 -Wall -pthread -g -fopenmp
Cflags = gcc -Wall -fopenmp -pthread
C++MPIflags = mpic++ -g
#g++ -Wall -std=c++11 -pthread eratosthenes.cpp -o eratosthenes
#g++ -Wall -std=c++11 -pthread eratosthenes_random.cpp -o eratosthenes_random
#chmod +x eratosthenes_sc.sh


all:
	$(MAKE) eratosthenes_mpi.exe

eratosthenes_mpi.exe:
	$(C++MPIflags) eratosthenes_mpi.cpp -o eratosthenes_mpi

run_eratosthenes_single: eratosthenes_mpi.exe
	mpiexec -np 1 --hostfile host ./eratosthenes_mpi 10000000
	mpiexec -np 2 --hostfile host ./eratosthenes_mpi 10000000
	mpiexec -np 16 --hostfile host ./eratosthenes_mpi 10000000
	mpiexec -np 32 --hostfile host ./eratosthenes_mpi 10000000
	
run_eratosthenes_all: eratosthenes_mpi.exe
	mpiexec -np 1 --hostfile hosts ./eratosthenes_mpi 10000000
	mpiexec -np 2 --hostfile hosts ./eratosthenes_mpi 10000000
	mpiexec -np 16 --hostfile hosts ./eratosthenes_mpi 10000000
	mpiexec -np 32 --hostfile hosts ./eratosthenes_mpi 10000000
	mpiexec -np 64 --hostfile hosts ./eratosthenes_mpi 10000000
	mpiexec -np 96 --hostfile hosts ./eratosthenes_mpi 10000000

eratosthenes_mpi_bc.exe:
	$(C++MPIflags) eratosthenes_mpi.cpp -o eratosthenes_mpi

run_eratosthenes_bc: eratosthenes_mpi_bc.exe
	mpiexec -np 1 --hostfile hosts ./eratosthenes_mpi_bc 10000000
	mpiexec -np 2 --hostfile hosts ./eratosthenes_mpi_bc 10000000
	mpiexec -np 16 --hostfile hosts ./eratosthenes_mpi_bc 10000000
	mpiexec -np 32 --hostfile hosts ./eratosthenes_mpi_bc 10000000
	mpiexec -np 64 --hostfile hosts ./eratosthenes_mpi_bc 10000000
	mpiexec -np 96 --hostfile hosts ./eratosthenes_mpi_bc 10000000
	
clean:
	$(RM) *.exe
	$(RM) *.pgm
	$(RM) *.gif

clean_win:
	del *.exe
	del *.pgm
	del *.gif