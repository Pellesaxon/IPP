#ifndef lacpp_sorted_list_fine_mutex_hpp
#define lacpp_sorted_list_fine_mutex_hpp lacpp_sorted_list_fine_mutex_hpp
#include <mutex>

/* a sorted list implementation by David Klaftenegger, 2015
 * please report bugs or suggest improvements to david.klaftenegger@it.uu.se
 */


/* non-concurrent sorted singly-linked list */
template<typename T>
class sorted_list_fine_mutex {
	/* struct for list nodes */
	private:
		struct node {
			std::mutex node_mutex;
			T value;
			node* next;
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
		sorted_list_fine_mutex() = default;
		sorted_list_fine_mutex(const sorted_list_fine_mutex<T>& other) = default;
		sorted_list_fine_mutex(sorted_list_fine_mutex<T>&& other) = default;
		sorted_list_fine_mutex<T>& operator=(const sorted_list_fine_mutex<T>& other) = default;
		sorted_list_fine_mutex<T>& operator=(sorted_list_fine_mutex<T>&& other) = default;
		~sorted_list_fine_mutex() {
			while(first != nullptr) {
				remove(first->value);
			}
		}
		/* insert v into the list */
		void insert(T v) {
			/* first find position */
			
			node* pred = nullptr;
			node* succ = first;
			while(succ != nullptr){
				succ->node_mutex.lock();

				if  (succ->value < v){
					break;
				}
				if (pred != nullptr){
					pred->node_mutex.unlock();
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
				succ->node_mutex.unlock();
			}

			if(pred == nullptr) {
				first = current;
			} else {
				pred->next = current;
				pred->node_mutex.unlock();
			}
		}

		void remove(T v) {
			/* first find position */
			node* pred = nullptr;
			node* current = first;
			

			while(current != nullptr){
				current->node_mutex.lock();

				if  (current->value < v){
					break;
				}
				if (pred != nullptr){
					pred->node_mutex.unlock();
				}
				pred = current;
				current = current->next;
			}

			if(current == nullptr || current->value != v) {
				/* v not found */
				if (pred != nullptr){
					pred->node_mutex.unlock();
				}
				if (current != nullptr){
					current->node_mutex.unlock();
				}
				return;
			}

			/* remove current */
			if(pred == nullptr) {
				first = current->next;
				/* We dont need to unlock as lock is deleted with current*/
			} else {
				pred->next = current->next;
				pred->node_mutex.unlock();
			}
			delete current;
		}

		/* count elements with value v in the list */
		std::size_t count(T v) {
			std::size_t cnt = 0;
			/* first go to value v */
			node* current = first;
			node* new_current;
			
			while(current != nullptr){
				current->node_mutex.lock();
				
				if  (current->value < v){
					break;
				}
				new_current = current->next;
				current->node_mutex.unlock();
				current = new_current;
			}
			
			/* count elements */
			while(current != nullptr && current->value == v) {
				cnt++;
				new_current = current->next;
				if (new_current != nullptr){
					new_current->node_mutex.lock();
				}

				current->node_mutex.unlock();
				current = new_current;
			}
			if (current != nullptr){
					current->node_mutex.unlock();
				}
			return cnt;
		}
};

#endif // lacpp_sorted_list_hpp
