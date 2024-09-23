C++flags = g++ -std=c++11 -Wall -pthread -fopenmp

#g++ -Wall -std=c++11 -pthread eratosthenes.cpp -o eratosthenes
#g++ -Wall -std=c++11 -pthread eratosthenes_random.cpp -o eratosthenes_random
#chmod +x eratosthenes_sc.sh'

threads = 4

all:
	$(MAKE)

hello_world_parallel.exe:
	$(C++flags) hello_world_parallel.cpp -o hello_world_parallel

pi_parallel.exe:
	$(C++flags) pi_parallel.cpp -o pi_parallel

pi_original.exe:
	$(C++flags) pi_original.cpp -o pi_original

run: hello_world_parallel.exe pi_parallel.exe
#	powershell -Command "$$env:OMP_NUM_THREADS=$(threads); ./hello_world_paralell.exe"
	./hello_world_parallel.exe
	./pi_parallel.exe


# pre_run:
# 	set OMP_NUM_THREADS=4


# trapeze.exe:
# 	$(C++flags) trapeze.cpp -o trapeze

# run_trapeze: trapeze.exe
# 	chmod +x trap_dynamic_sc.sh
# 	./trap_dynamic_sc.sh


clean:
	$(RM) *.exe

wclean:
	del *.exe