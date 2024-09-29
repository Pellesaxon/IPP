C++flags = g++ -std=c++11 -Wall -pthread -g

#g++ -Wall -std=c++11 -pthread eratosthenes.cpp -o eratosthenes
#g++ -Wall -std=c++11 -pthread eratosthenes_random.cpp -o eratosthenes_random
#chmod +x eratosthenes_sc.sh


all:
	$(MAKE) trapeze.exe
	$(MAKE) dtrapeze.exe


trapeze.exe:
	$(C++flags) trapeze.cpp -o trapeze

run_trapeze: trapeze.exe
	chmod +x trap_dynamic_sc.sh
	./trap_dynamic_sc.sh

dtrapeze.exe:
	$(C++flags) trapeze_dynamic.cpp -o dtrapeze

run_dtrapeze: dtrapeze.exe
	chmod +x trap_dynamic_sc.sh
	./trap_dynamic_sc.sh

eratosthenes.exe:
	$(C++flags) eratosthenes.cpp -o eratosthenes

eratosthenes_random.exe:
	$(C++flags) eratosthenes_random.cpp -o eratosthenes_random

run_eratosthenes: eratosthenes.exe eratosthenes_random.exe
	chmod +x eratosthenes_sc.sh
	./eratosthenes_sc.sh

bench.exe:
	g++ -std=c++20 -Wall -pthread -g benchmark_example.cpp -o bench

run_bench: bench.exe
	./bench.exe 4

clean:
	$(RM) *.exe