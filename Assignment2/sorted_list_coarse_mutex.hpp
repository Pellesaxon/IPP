#ifndef lacpp_sorted_list_coarse_mutex_hpp
#define lacpp_sorted_list_coarse_mutex_hpp lacpp_sorted_list_coarse_mutex_hpp
#include <mutex>

/* a sorted list implementation by David Klaftenegger, 2015
 * please report bugs or suggest improvements to david.klaftenegger@it.uu.se
 */



/* non-concurrent sorted singly-linked list */
template<typename T>
class sorted_list_coarse_mutex {
	/* struct for list nodes */
	private:
		struct node {
			T value;
			node* next;
		};


	node* first = nullptr;
	std::mutex sorted_list_mutex;

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
		sorted_list_coarse_mutex() = default;
		sorted_list_coarse_mutex(const sorted_list_coarse_mutex<T>& other) = default;
		sorted_list_coarse_mutex(sorted_list_coarse_mutex<T>&& other) = default;
		sorted_list_coarse_mutex<T>& operator=(const sorted_list_coarse_mutex<T>& other) = default;
		sorted_list_coarse_mutex<T>& operator=(sorted_list_coarse_mutex<T>&& other) = default;
		~sorted_list_coarse_mutex() {
			while(first != nullptr) {
				remove(first->value);
			}
		}
		/* insert v into the list */
		void insert(T v) {
			sorted_list_mutex.lock();
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
			sorted_list_mutex.unlock();
		}

		void remove(T v) {
			sorted_list_mutex.lock();
			/* first find position */
			node* pred = nullptr;
			node* current = first;
			while(current != nullptr && current->value < v) {
				pred = current;
				current = current->next;
			}
			if(current == nullptr || current->value != v) {
				/* v not found */
				sorted_list_mutex.unlock();
				return;
			}
			/* remove current */
			if(pred == nullptr) {
				first = current->next;
			} else {
				pred->next = current->next;
			}
			delete current;
			sorted_list_mutex.unlock();
		}

		/* count elements with value v in the list */
		std::size_t count(T v) {
			sorted_list_mutex.lock();
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
			sorted_list_mutex.unlock();
			return cnt;
		}
};

#endif // lacpp_sorted_list_hpp
