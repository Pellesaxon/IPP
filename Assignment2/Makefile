C++flags = g++ -std=c++11 -Wall -pthread

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
	g++ -Wall -std=c++11 -pthread eratosthenes.cpp -o eratosthenes

eratosthenes_random.exe:
	g++ -Wall -std=c++11 -pthread eratosthenes_random.cpp -o eratosthenes_random

run_eratosthenes: eratosthenes.exe eratosthenes_random.exe
	chmod +x eratosthenes_sc.sh
	./eratosthenes_sc.sh

clean:
	$(RM) *.exe