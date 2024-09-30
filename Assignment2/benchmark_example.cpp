#include <cstdlib>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "benchmark.hpp"
#include "sorted_list_coarse_mutex.hpp"
#include "sorted_list_fine_mutex.hpp"
#include "sorted_list_coarse_TATAS.hpp"
#include "sorted_list_fine_TATAS.hpp"
#include "sorted_list_fine_CLH.hpp"

static const int DATA_VALUE_RANGE_MIN = 0;
static const int DATA_VALUE_RANGE_MAX = 256;
static const int DATA_PREFILL = 512;

template<typename List>
void read(List& l, int random) {
	/* read operations: 100% count */
	l.count(random % DATA_VALUE_RANGE_MAX);
}

template<typename List>
void update(List& l, int random) {
	/* update operations: 50% insert, 50% remove */
	auto choice = (random % (2*DATA_VALUE_RANGE_MAX))/DATA_VALUE_RANGE_MAX;
	if(choice == 0) {
		l.insert(random % DATA_VALUE_RANGE_MAX);
	} else {
		l.remove(random % DATA_VALUE_RANGE_MAX);
	}
}

template<typename List>
void mixed(List& l, int random) {
	/* mixed operations: 6.25% update, 93.75% count */
	auto choice = (random % (32*DATA_VALUE_RANGE_MAX))/DATA_VALUE_RANGE_MAX;
	if(choice == 0) {
		l.insert(random % DATA_VALUE_RANGE_MAX);
	} else if(choice == 1) {
		l.remove(random % DATA_VALUE_RANGE_MAX);
	} else {
		l.count(random % DATA_VALUE_RANGE_MAX);
	}
}
template <typename T>
thread_local std::unique_ptr<typename sorted_list_fine_CLH<T>::CLHlock::Qnode> sorted_list_fine_CLH<T>::CLHlock::my_node(new typename sorted_list_fine_CLH<T>::CLHlock::Qnode());

template <typename T>
thread_local typename sorted_list_fine_CLH<T>::CLHlock::Qnode* sorted_list_fine_CLH<T>::CLHlock::my_pred = nullptr;

template <typename T>
void initThreadLocal(){
	sorted_list_fine_CLH<T>::CLHlock::my_node.get();
    sorted_list_fine_CLH<T>::CLHlock::my_pred = nullptr;
}


int main(int argc, char* argv[]) {
	/* get number of threads from command line */
	if(argc < 2) {
		std::cerr << "Please specify number of worker threads: " << argv[0] << " <number>\n";
		std::exit(EXIT_FAILURE);
	}
	std::istringstream ss(argv[1]);
	int threadcnt;
	if (!(ss >> threadcnt)) {
		std::cerr << "Invalid number of threads '" << argv[1] << "'\n";
		std::exit(EXIT_FAILURE);
	}
	/* set up random number generator */
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> uniform_dist(DATA_VALUE_RANGE_MIN, DATA_VALUE_RANGE_MAX);

	// /* Benchmarking coarse mutex*/
	// sorted_list_coarse_mutex<int> l1;
	// /* prefill list with 1024 elements */
	// for(int i = 0; i < DATA_PREFILL; i++) {
	// 	l1.insert(uniform_dist(engine));
	// }
	// benchmark(threadcnt, "coarse_mutex read", [&l1](int random){
	// 	read(l1, random);
	// });
	// benchmark(threadcnt, "coarse_mutex update", [&l1](int random){
	// 	update(l1, random);
	// });
	// /* start with fresh list: update test left list in random size */
	// sorted_list_coarse_mutex<int> l2;
	// /* prefill list with 1024 elements */
	// for(int i = 0; i < DATA_PREFILL; i++) {
	// 	l2.insert(uniform_dist(engine));
	// }
	// benchmark(threadcnt, "coarse_mutex mixed", [&l2](int random){
	// 	mixed(l2, random);
	// });


	// /* Benchmarking fine mutex*/
	// sorted_list_fine_mutex<int> l3;
	// /* prefill list with 1024 elements */
	// for(int i = 0; i < DATA_PREFILL; i++) {
	// 	l3.insert(uniform_dist(engine));
	// }
	// benchmark(threadcnt, "fine-mutex read", [&l3](int random){
	// 	read(l3, random);
	// });
	// benchmark(threadcnt, "fine-mutex update", [&l3](int random){
	// 	update(l3, random);
	// });

	// /* start with fresh list: update test left list in random size */
	// sorted_list_fine_mutex<int> l4;
	// /* prefill list with 1024 elements */
	// for(int i = 0; i < DATA_PREFILL; i++) {
	// 	l4.insert(uniform_dist(engine));
	// }

	// benchmark(threadcnt, "fine-mutex mixed", [&l4](int random){
	// 	mixed(l4, random);
	// });
	// //This shouldn't be needed but theory is that some references to something somewhere in the code doesn't decrease to 0 and it therefore never quits
	// l3 = sorted_list_fine_mutex<int>();
	// l4 = sorted_list_fine_mutex<int>();

	// /* Benchmarking course TATAS*/
	// sorted_list_coarse_TATAS<int> l5;
	// /* prefill list with 1024 elements */
	// for(int i = 0; i < DATA_PREFILL; i++) {
	// 	l5.insert(uniform_dist(engine));
	// }
	// benchmark(threadcnt, "coarse_TATAS read", [&l5](int random){
	// 	read(l5, random);
	// });
	// benchmark(threadcnt, "coarse_TATAS update", [&l5](int random){
	// 	update(l5, random);
	// });

	// /* start with fresh list: update test left list in random size */
	// sorted_list_coarse_TATAS<int> l6;
	// /* prefill list with 1024 elements */
	// for(int i = 0; i < DATA_PREFILL; i++) {
	// 	l6.insert(uniform_dist(engine));
	// }
	// benchmark(threadcnt, "coarse_TATAS mixed", [&l6](int random){
	// 	mixed(l6, random);
	// });

	// /* Benchmarking fine mutex*/
	// sorted_list_fine_TATAS<int> l7;
	// /* prefill list with 1024 elements */
	// for(int i = 0; i < DATA_PREFILL; i++) {
	// 	l7.insert(uniform_dist(engine));
	// }
	// benchmark(threadcnt, "fine_TATAS read", [&l7](int random){
	// 	read(l7, random);
	// });
	// benchmark(threadcnt, "fine_TATAS update", [&l7](int random){
	// 	update(l7, random);
	// });

	// /* start with fresh list: update test left list in random size */
	// sorted_list_fine_TATAS<int> l8;
	// /* prefill list with 1024 elements */
	// for(int i = 0; i < DATA_PREFILL; i++) {
	// 	l8.insert(uniform_dist(engine));
	// }
	// benchmark(threadcnt, "fine_TATAS mixed", [&l8](int random){
	// 	mixed(l8, random);
	// });

	/* Benchmarking fine mutex*/
	initThreadLocal<int>();
	sorted_list_fine_CLH<int> l9;
	/* prefill list with 1024 elements */
	for(int i = 0; i < DATA_PREFILL; i++) {
		l9.insert(uniform_dist(engine));
	}
	benchmark(threadcnt, "fine_CLH read", [&l9](int random){
		read(l9, random);
	});
	benchmark(threadcnt, "fine_CLH update", [&l9](int random){
		update(l9, random);
	});

	/* start with fresh list: update test left list in random size */
	sorted_list_fine_CLH<int> l10;
	/* prefill list with 1024 elements */
	for(int i = 0; i < DATA_PREFILL; i++) {
		l10.insert(uniform_dist(engine));
	}
	benchmark(threadcnt, "fine_CLH mixed", [&l10](int random){
		mixed(l10, random);
	});
	

	//This shouldn't be needed but theory is that some references to something somewhere in the code doesn't decrease to 0 and it therefore never quits
	// l7 = sorted_list_fine_TATAS<int>();
	// l8 = sorted_list_fine_TATAS<int>();
	l9 = sorted_list_fine_CLH<int>();
	l10 = sorted_list_fine_CLH<int>();
	std::cout<<"Done";

	return EXIT_SUCCESS;
}
