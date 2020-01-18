#include "Split_Queue.h"
#include <thread>
#include <iostream>
#define TEST_LEN 100000
#define LOW_TEST 10
#define HIGH_TEST 100
using namespace std;
void count(int x,Split_Queue<int>* q){
	for(int i=0;i<x;i++){
		q->push(i);
	}
} 
void var(int x,Queue_Head<int>* q){
	bool ret=true;
	for(int i=0;i<x;i++){
		while(q->empty());
		
		if(q->pop()!=i) ret=false;

	}
	
	if(!ret){
		cout<<q<<"Failed"<<endl;
	}
} 
int slowFibonachi(int x){
	if(x<2){
		return 1;
	}else{
		return slowFibonachi(x-1)+slowFibonachi(x-2);
	}

}
void bog(int x,Split_Queue<int>*q){
	for(int i=0;i<x;i++){
		q->push(slowFibonachi(i));
	}
}

int main(){
	{
		cout<<"Initilizing base Queue"<<endl;
		Split_Queue<int> baseQueue;
		cout<<"registering thread"<<endl;
		Queue_Head<int>*  head=baseQueue.registerThread();
		cout<<"enqueue test"<<endl;
		count(10,&baseQueue);
		cout<<"dequeue test"<<endl;
		var(10,head);
	}
cout<<"\nStarting 1 thread tests"<<endl;
	{
		Split_Queue<int> baseQueue;
		cout<<"registering thread"<<endl;
		thread test(var,10,baseQueue.registerThread() );
		cout<<"enqueue test"<<endl;
		count(10,&baseQueue);
		test.join();	
		cout<<"finished test"<<endl;
		
 
	}
cout<<"\nStarting large test"<<endl;
	{
		Split_Queue<int> baseQueue;
		cout<<"registering thread"<<endl;
		thread test(var,TEST_LEN,baseQueue.registerThread() );
		cout<<"enqueue test"<<endl;
		count(TEST_LEN,&baseQueue);
		test.join();	
		cout<<"finished test"<<endl;
		
 
	}
	cout<<"\nStarting "<<LOW_TEST<<" thread tests"<<endl;
	{
		Split_Queue<int> baseQueue;
		cout<<"registering threads"<<endl;
		thread test[LOW_TEST];
		for(int i=0;i<LOW_TEST;i++){
			test[i]=thread(var,10,baseQueue.registerThread() );
		}
		cout<<"enqueue test"<<endl;
		count(10,&baseQueue);
		for(int i=0;i<LOW_TEST;i++){
			test[i].join();
		}
		cout<<"finished test"<<endl;
		
 
	}

cout<<"\nStarting large test"<<endl;
	{
		Split_Queue<int> baseQueue;
		cout<<"registering threads"<<endl;
		thread test[LOW_TEST];
		for(int i=0;i<LOW_TEST;i++){
			test[i]=thread(var,TEST_LEN,baseQueue.registerThread() );
		}
		cout<<"enqueue test"<<endl;
		count(TEST_LEN,&baseQueue);
		for(int i=0;i<LOW_TEST;i++){
			test[i].join();
		}
		cout<<"finished test"<<endl;
		
 
	}

	cout<<"\nStarting "<<HIGH_TEST<<" thread tests"<<endl;
	{
		Split_Queue<int> baseQueue;
		cout<<"registering threads"<<endl;
		thread test[HIGH_TEST];
		for(int i=0;i<HIGH_TEST;i++){
			test[i]=thread(var,10,baseQueue.registerThread() );
		}
		cout<<"enqueue test"<<endl;
		count(10,&baseQueue);
		for(int i=0;i<HIGH_TEST;i++){
			test[i].join();
		}
		cout<<"finished test"<<endl;
		
 
	}

cout<<"\nStarting large test"<<endl;
	{
		Split_Queue<int> baseQueue;
		cout<<"registering threads"<<endl;
		thread test[HIGH_TEST];
		for(int i=0;i<HIGH_TEST;i++){
			test[i]=thread(var,TEST_LEN,baseQueue.registerThread() );
		}
		cout<<"enqueue test"<<endl;
		count(TEST_LEN,&baseQueue);
		for(int i=0;i<HIGH_TEST;i++){
			test[i].join();
		}
		cout<<"finished test"<<endl;
		
 
	}
}
