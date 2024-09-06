C++flags = g++ -std=c++20 -Wall -pthread

all:
	$(C++flags) performance.cpp -o performance
	$(C++flags) non-determinism.cpp -o non-determinism
	$(C++flags) shared-variable.cpp -o shared-variable
	$(C++flags) dining.cpp -o dining
	$(C++flags) diningSolved.cpp -o diningSolved

clean:
	$(RM) *.exe