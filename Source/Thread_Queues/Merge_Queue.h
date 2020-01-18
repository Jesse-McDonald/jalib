//A queue designed to be
//	1. Non blocking
//	2. Thread safe enqueue from n threads
//	3. Dequeue safe 1 n parralell enqueue
//	4. Dequeue will be o(1) if queue is densly populated and worst case of o(n) otherwise.
//		(As the queue is designed for piping data/tasks from branch Threads, if there is little to do, it is ok if it takes a while)

//Note, data race conditions still apply to order of dequeued objects, you are not gaurenteed
//that objects will be dequeued in the exact order they where enqueued, but they will be in the right approximate order

//to register a new thread, call registerThread and pass the resulting pointer to the thread.
// each thread should be registered independently.
//Registering is thread safe using mutexes, but is recomended to only happen in read thread

#ifndef MERGE_QUEUE_H
#define MERGE_QUEUE_H
#include <mutex>
#include <memory>
#include <vector>
template<class T>
class Queue_Node{
	public:
	T data;
	Queue_Node<T> * next;
	Queue_Node(){
		next=nullptr;
	}
	Queue_Node(T idata){
		data=idata;
		next=nullptr;
	}
};


template<class T>
class Queue{
	public:
	Queue_Node<T>* head;
	Queue_Node<T>* tail;
	Queue(){
		head=nullptr;
		tail=nullptr;
		
	}
	bool empty(){
		if(head==nullptr){
	
			return true;

		}else if(emptied){

			if(head->next==nullptr){
				
				return true;
			}else{
				emptied=false;
				
				head=head->next;//we were emptied, but no longer, clear out slag node
			}
		}
		return false;
	}
	T peek(){
			
		if(empty()){
			return T();
		}else{
			return head->data;
		}
	}
	inline T top(){
		
		return peek();
	}
	T dequeue(){
		if(empty()){
			return T();
		}else{
			Queue_Node<T>* tmp=head;
			if(tmp->next==nullptr){
				emptied=true;
				
				return tmp->data;
			}else{
				head=tmp->next;
				T ret=tmp->data;
				delete tmp; 
				return ret;
			}
		}
	}
	inline T pop(){
		return dequeue();
	}
	Queue<T>& enqueue(T data){
		if(tail==nullptr){//should only trigger on initial enqueue
			head=new Queue_Node<T>(data);
			tail=head;
		}else{
			tail->next=new Queue_Node<T>(data);
			tail=tail->next;
		}
		return *this;
	}
	inline Queue<T>& push(T data){
		return enqueue(data);
	}
	inline Queue<T>& operator<<(T data){
		return enqueue(data);
	}
	inline	Queue<T>& operator>>(T& data){
		data= dequeue();
		return *this;
	}
	protected:

	bool emptied=false;
};
template<class T, class Q=Queue<T>>
class Merge_Queue{
	public:
	Merge_Queue(){
		regLock=std::make_shared<std::mutex>();
		index=0;
	}
	
	Q * registerThread(){//registred pointers die with parrent Thread Queue
		std::shared_ptr<Q> queue=std::make_shared<Q>();
		
		regLock->lock();
		queues.push_back(queue);
		regLock->unlock();
		return queue.get();
	}
	T peek(){
		for(int i=0;i<queues.size();i++){

			if(!queues[index]->empty()){
				return queues[index]->top();
			}
			index++;
			index%=queues.size();
		}
		return T();
	}
	inline T top(){
		return peek();
	}
	T dequeue(){
		for(int i=0;i<queues.size();i++){

			if(!queues[index]->empty()){

				return queues[index]->pop();
			}
			index++;
			index%=queues.size();
		}
		return T();
	}
	inline T pop(){
			return dequeue();
	}
	bool empty(){
		for(int i=0;i<queues.size();i++){
			if(!queues[index]->empty()){
				
				return false;
			}
			index++;
			index%=queues.size();
		}
		return true;
	}
	virtual ~Merge_Queue(){}
	protected:
	
	std::shared_ptr<std::mutex>regLock;
	size_t index;
	std::vector<std::shared_ptr<Q>> queues;
};
#endif
