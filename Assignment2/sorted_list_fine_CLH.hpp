#ifndef lacpp_sorted_list_fine_CLH_hpp
#define lacpp_sorted_list_fine_CLH_hpp lacpp_sorted_list_fine_CLH_hpp
#include <atomic>

/* a sorted list implementation by David Klaftenegger, 2015
 * please report bugs or suggest improvements to david.klaftenegger@it.uu.se
 */


/* non-concurrent sorted singly-linked list */
// Define and initialize thread-local variables

template <typename T>
class sorted_list_fine_CLH {
	/* struct for list nodes */
		/* Based on proposed structure from lecture as well as the course book
		https://stackoverflow.com/questions/2785612/c-what-does-the-colon-after-a-constructor-mean
		https://www.cs.rochester.edu/research/synchronization/pseudocode/ss.html#clh
		https://codereview.stackexchange.com/questions/184407/c11-clh-lock-implementation
		*/
	public:
		class CLHlock {	
		public: 
			struct Qnode{
				std::atomic_bool locked {false};
			};
		
		public:
			std::atomic<Qnode *> tail;
			thread_local static std::unique_ptr<Qnode> my_node;
			thread_local static Qnode* my_pred;
		
		public: 
			CLHlock(){
				Qnode* tmp = new Qnode();
				tmp -> locked.store(false);
				tail = tmp;
			}
			void lock() {
				my_node->locked.store(true);
				my_pred = tail.exchange(my_node.get());
				while(my_pred->locked.load()){
					std::cout<<"Stuck in lock ";
				}
				std::cout<<"Locked node ";
			}
			void unlock() {
				my_node->locked.store(false);
				Qnode* tmp = my_pred;
				my_pred = my_node.release();
				my_node.reset(tmp);
				std::cout<<"Unlocked node ";
			}
			~CLHlock(){
				delete tail;
			}
		};

	private:
		struct node {
			T value;
			node* next;
			CLHlock node_lock;
		};
		
	node* first = nullptr;
	
	//thread_local std::unique_ptr<typename CLHlock::Qnode> CLHlock::my_node = new CLHlock::Qnode;
	//thread_local typename CLHlock::Qnode* CLHlock::my_pred = nullptr;

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
		sorted_list_fine_CLH() {
			// thread_local std::unique_ptr<CLHlock::Qnode> CLHlock::my_node(new CLHlock::Qnode);
			// thread_local CLHlock::Qnode* CLHlock::my_pred = nullptr;
		};
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
