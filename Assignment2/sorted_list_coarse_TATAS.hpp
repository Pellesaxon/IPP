#ifndef lacpp_sorted_list_coarse_TATAS_hpp
#define lacpp_sorted_list_coarse_TATAS_hpp lacpp_sorted_list_coarse_TATAS_hpp
#include <atomic>

/* a sorted list implementation by David Klaftenegger, 2015
 * please report bugs or suggest improvements to david.klaftenegger@it.uu.se
 */



/* non-concurrent sorted singly-linked list */
template<typename T>
class sorted_list_coarse_TATAS {
	/* struct for list nodes */
	private:
		struct node {
			T value;
			node* next;
		};

		/* Based on proposed structure from lecture*/
		class TATASlock {
			std::atomic_bool ready {false};
			public: bool get() {
				return ready.load();
			}
			public: void lock() {
				while (true){
					while (get()) {}
					if (!ready.exchange(true))
					return;
				}
			}
			public: void unlock() {
				ready.store(false);
			}
		};


	node* first = nullptr;
	TATASlock node_lock;


	public:
		/* default implementations:
		 * default constructor
		 * copy constructor (note: shallow copy)
		 * move constructor
		 * copy assignment operator (note: shallow copy)
		 * move assignment operator
		 *
		 * The first is required due to the others,
		 * which are explicitly listed due to the rule of five.
		 */
		sorted_list_coarse_TATAS() = default;
		sorted_list_coarse_TATAS(const sorted_list_coarse_TATAS<T>& other) = default;
		sorted_list_coarse_TATAS(sorted_list_coarse_TATAS<T>&& other) = default;
		sorted_list_coarse_TATAS<T>& operator=(const sorted_list_coarse_TATAS<T>& other) = default;
		sorted_list_coarse_TATAS<T>& operator=(sorted_list_coarse_TATAS<T>&& other) = default;
		~sorted_list_coarse_TATAS() {
			while(first != nullptr) {
				remove(first->value);
			}
		}
		/* insert v into the list */
		void insert(T v) {
			node_lock.lock();
			/* first find position */
			node* pred = nullptr;
			node* succ = first;
			while(succ != nullptr && succ->value < v) {
				pred = succ;
				succ = succ->next;
			}
			
			/* construct new node */
			node* current = new node();
			current->value = v;

			/* insert new node between pred and succ */
			current->next = succ;
			if(pred == nullptr) {
				first = current;
			} else {
				pred->next = current;
			}
			node_lock.unlock();
		}

		void remove(T v) {
			node_lock.lock();
			/* first find position */
			node* pred = nullptr;
			node* current = first;
			while(current != nullptr && current->value < v) {
				pred = current;
				current = current->next;
			}
			if(current == nullptr || current->value != v) {
				/* v not found */
				node_lock.unlock();
				return;
			}
			/* remove current */
			if(pred == nullptr) {
				first = current->next;
			} else {
				pred->next = current->next;
			}
			delete current;
			node_lock.unlock();
		}

		/* count elements with value v in the list */
		std::size_t count(T v) {
			node_lock.lock();
			std::size_t cnt = 0;
			/* first go to value v */
			node* current = first;
			while(current != nullptr && current->value < v) {
				current = current->next;
			}
			/* count elements */
			while(current != nullptr && current->value == v) {
				cnt++;
				current = current->next;
			}
			node_lock.unlock();
			return cnt;
		}
};

#endif // lacpp_sorted_list_hpp
