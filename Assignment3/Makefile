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

run_gol: gol.exe
	chmod +x gol_sc.sh
	./gol_sc.sh

gol_print.exe:
	$(Cflags) Game_Of_Life.c -o gol_print -DOUTPUT

run_gol_print: gol_print.exe
	./gol_print 64 300 4

matrix.exe:
	$(C++flags) matrix.cpp -o matrix

run_matrix: matrix.exe
	chmod +x matrix_sc.sh
	./matrix_sc.sh

gaus_row.exe:
	$(C++flags) gaus_row.cpp -o gaus_row

gaus_col.exe:
	$(C++flags) gaus_col.cpp -o gaus_col

run_gaus: gaus_row.exe gaus_col.exe
	./gaus_row 6400 8
	./gaus_row 6400 4
	./gaus_row 6400 2
	./gaus_col 6400 8
	./gaus_col 6400 4
	./gaus_col 6400 2
clean:
	$(RM) *.exe
	$(RM) *.pgm
	$(RM) *.gif

clean_win:
	del *.exe
	del *.pgm
	del *.gif