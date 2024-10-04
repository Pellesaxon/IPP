C++flags = g++ -std=c++11 -Wall -pthread -g -fopenmp
Cflags = gcc -Wall -fopenmp -pthread
#g++ -Wall -std=c++11 -pthread eratosthenes.cpp -o eratosthenes
#g++ -Wall -std=c++11 -pthread eratosthenes_random.cpp -o eratosthenes_random
#chmod +x eratosthenes_sc.sh


all:
	
eratosthenes_omp.exe:
	$(C++flags) eratosthenes_omp.cpp -o eratosthenes_omp

run_eratosthenes: eratosthenes_omp.exe 
	chmod +x eratosthenes_sc.sh
	./eratosthenes_sc.sh

gol.exe:
	$(Cflags) Game_Of_Life.c -o gol

run_gol:
	

clean:
	$(RM) *.exe
	$(RM) *.pgm
	$(RM) *.gif

clean_win:
	del *.exe
	del *.pgm
	del *.gif