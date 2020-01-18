//A queue designed to be
//	1. Non blocking
//	2. Thread safe dequeue from n threads
//	3. Enqueue safe for n parralell Dequeues
//	4. Dequeue will be o(1)
//	5. Enqueue will be o(1)
//	6. All enqueued objects are dequed by each thread
//	7. For n enqueues, memory shall not excede n
#ifndef SPLIT_QUEUE_H
#define SPLIT_QUEUE_H

#include <memory>
template<class T>
class Shared_Queue_Node{
	public:
	T data;
	std::shared_ptr<Shared_Queue_Node<T>>  next;
	Shared_Queue_Node(){}
	Shared_Queue_Node(T idata){
		data=idata;
	}
};


template<class T>
class Queue_Head{
	public:
	Queue_Head(){}
	Queue_Head(std::shared_ptr<Shared_Queue_Node<T>> ihead){head=ihead;}
	
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
	inline T dequeue(){
		if(empty()){
			return T();
		}else{
			std::shared_ptr<Shared_Queue_Node<T>> tmp=head;
			if(tmp->next==nullptr){
				emptied=true;
				return tmp->data;
			}else{
				head=tmp->next;
				T ret=tmp->data; 
				return ret;
			}
		}
	}
	inline T pop(){
		return dequeue();
	}
	inline	Queue_Head<T>& operator>>(T& data){
		data= dequeue();
		return *this;
	}
	protected:
	std::shared_ptr<Shared_Queue_Node<T>> head;
	bool emptied=true;
};
 

template<class T>
class Split_Queue{

	public:
	Queue_Head<T>* registerThread(){
		
		return new Queue_Head<T>(tail); 
	}
	Split_Queue(){
		//make dummy node so that pointers of it can be taken
		tail=std::make_shared<Shared_Queue_Node<T>>(-1);

	}
	
	Split_Queue<T>& enqueue(T data){
	
			
			tail->next=std::make_shared<Shared_Queue_Node<T>>(data);
			tail=tail->next;

		return *this;
	}
	inline Split_Queue<T>& push(T data){
		return enqueue(data);
	}
	inline Split_Queue<T>& operator<<(T data){
		return enqueue(data);
	}


	virtual ~Split_Queue(){
	}
	protected:
	std::shared_ptr<Shared_Queue_Node<T>> tail;
};
#endif
