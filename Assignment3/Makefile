C++flags = g++ -std=c++11 -Wall -pthread -g -fopenmp

#g++ -Wall -std=c++11 -pthread eratosthenes.cpp -o eratosthenes
#g++ -Wall -std=c++11 -pthread eratosthenes_random.cpp -o eratosthenes_random
#chmod +x eratosthenes_sc.sh


all:
	
eratosthenes_omp.exe:
	$(C++flags) eratosthenes_omp.cpp -o eratosthenes_omp

run_eratosthenes: eratosthenes_omp.exe 
	chmod +x eratosthenes_sc.sh
	./eratosthenes_sc.sh


clean:
	$(RM) *.exe