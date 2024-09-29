#ifndef lacpp_sorted_list_fine_CLH_hpp
#define lacpp_sorted_list_fine_CLH_hpp lacpp_sorted_list_fine_CLH_hpp
#include <atomic>

/* a sorted list implementation by David Klaftenegger, 2015
 * please report bugs or suggest improvements to david.klaftenegger@it.uu.se
 */


/* non-concurrent sorted singly-linked list */
template<typename T>
class sorted_list_fine_CLH {
	/* struct for list nodes */
	private:

		/* Based on proposed structure from lecture as well as the course book*/
		class CLHlock {
			struct Qnode{
				std::atomic_bool locked {true};
			};
			std::atomic_ref<Qnode> tail = &Qnode();
			
			thread_local static Qnode my_node;
			thread_local static Qnode* my_pred;
			
			public: void lock() {
				my_node = Qnode();
				my_pred = &tail.exchange(my_node);
				while(my_pred.locked.load()){}
			}
			public: void unlock() {
				my_node.locked.store(false);
				my_node = my_pred;
			}
		};

		struct node {
			T value;
			node* next;
			CLHlock node_lock;
		};
		
	node* first = nullptr;

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
		sorted_list_fine_CLH() = default;
		sorted_list_fine_CLH(const sorted_list_fine_CLH<T>& other) = default;
		sorted_list_fine_CLH(sorted_list_fine_CLH<T>&& other) = default;
		sorted_list_fine_CLH<T>& operator=(const sorted_list_fine_CLH<T>& other) = default;
		sorted_list_fine_CLH<T>& operator=(sorted_list_fine_CLH<T>&& other) = default;
		~sorted_list_fine_CLH() {
			while(first != nullptr) {
				remove(first->value);
			}
		}
		/* insert v into the list */
		void insert(T v) {
			/* first find position */
			// insert_lock.lock();
			node* pred = nullptr;
			node* succ = first;
			while(succ != nullptr){
				succ->node_lock.lock();

				if  (succ->value > v){
					break;
				}
				if (pred != nullptr){
					pred->node_lock.unlock();
				}
				pred = succ;
				succ = succ->next;
			}
			
			/* construct new node */
			node* current = new node();
			current->value = v;

			/* insert new node between pred and succ */
			current->next = succ;
			if (succ != nullptr){
				succ->node_lock.unlock();
			}

			if(pred == nullptr) {
				first = current;
			} else {
				pred->next = current;
				pred->node_lock.unlock();
			}
			// insert_lock.unlock();
		}

		void remove(T v) {
			/* first find position */
			// remove_lock.lock();
			node* pred = nullptr;
			node* current = first;
			

			while(current != nullptr){
				current->node_lock.lock();

				if  (current->value > v){
					break;
				}
				if (pred != nullptr){
					pred->node_lock.unlock();
				}
				pred = current;
				current = current->next;
			}

			if(current == nullptr || current->value != v) {
				/* v not found */
				if (current != nullptr){
					current->node_lock.unlock();
				}
				if (pred != nullptr){
					pred->node_lock.unlock();
				}
				// remove_lock.unlock();
				return;
			}

			/* remove current */
			if(pred == nullptr) {
				first = current->next;
				/* We dont need to unlock as lock is deleted with current*/
			} else {
				pred->next = current->next;
			}
			current->node_lock.unlock();
			pred->node_lock.unlock();
			delete current;
			// remove_lock.unlock();
		}

		/* count elements with value v in the list */
		std::size_t count(T v) {
			//count_lock.lock();
			std::size_t cnt = 0;
			/* first go to value v */
			node* current = first;
			node* new_current;
			
			while(current != nullptr){
				current->node_lock.lock();
				
				if  (current->value > v){
					break;
				}
				new_current = current->next;
				current->node_lock.unlock();
				current = new_current;
			}
			
			/* count elements */
			while(current != nullptr && current->value == v) {
				cnt++;
				new_current = current->next;
				if (new_current != nullptr){
					new_current->node_lock.lock();
				}

				current->node_lock.unlock();
				current = new_current;
			}
			if (current != nullptr){
					current->node_lock.unlock();
				}
			//count_lock.unlock();
			return cnt;
		}
};

#endif // lacpp_sorted_list_hpp
