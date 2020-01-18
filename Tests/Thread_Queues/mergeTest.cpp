#include "Merge_Queue.h"
#include <thread>
#include <iostream>
#define TEST_LEN 100000
#define LOW_TEST 10
#define HIGH_TEST 100
using namespace std;


void count(int x,Queue<int>* q){
	for(int i=0;i<x;i++){
		q->push(i);
	}
} 
int slowFibonachi(int x){
	if(x<2){
		return 1;
	}else{
		return slowFibonachi(x-1)+slowFibonachi(x-2);
	}

}
void bog(int x,Queue<int>*q){
	for(int i=0;i<x;i++){
		q->push(slowFibonachi(i));
	}
}
int main(){

	{//Test just QUEUE	
		cout<<"Testing QUEUE by its self"<<endl;
		Queue<int> threadQ;
		cout<<"Starting mono TEST 1"<<endl;
		thread monoTest(count,10,&threadQ);
		bool fail=false;
		for(int i=0;i<10;i++){
			while(threadQ.empty());
			if(threadQ.top()!=i){
				fail=true;
			}
			cout<<threadQ.pop()<<" ";
			
		}
		if(fail){
			cout<<"\nMono test 1 failed"<<endl;
		} else{
			cout<<"\nMono test 1 passed"<<endl;
		}
		cout<<"joining thread"<<endl;
		monoTest.join();
		cout<<"Starting mono Test 2"<<endl;
		monoTest=thread(count,TEST_LEN,&threadQ);
		for(int i=0;i<TEST_LEN;i++){
			while(threadQ.empty());
			threadQ.pop();
		}
		cout<<"Mono test 1 passed"<<endl<<endl;
		monoTest.join();
	}
	{//test Thread QUeue with 1 thread

		cout<<"Starting test with 1 Thread"<<endl;
		cout<<"Creating initial Queue"<<endl;
		Merge_Queue<int> q;
		cout<<"registering thread"<<endl;
		Queue<int>* threadQ=q.registerThread();
		cout<<"Starting mono TEST 1 "<<endl;
		thread monoTest(count,10,threadQ);
		bool fail=false;
		for(int i=0;i<10;i++){
				
			while(q.empty());

			if(q.top()!=i){
				fail=true;
			}
			cout<<q.pop()<<" ";
		}
		if(fail){
			cout<<"\nMono test 1 failed"<<endl;
		} else{
			cout<<"\nMono test 1 passed"<<endl;
		}
		cout<<"joining thread"<<endl;
		monoTest.join();
		cout<<"Starting mono Test 2"<<endl;
		monoTest=thread(count,TEST_LEN,threadQ);

		for(int i=0;i<TEST_LEN;i++){

			while(q.empty());
			q.pop();
		}
		cout<<"Mono test 1 passed"<<endl<<endl;
		monoTest.join();
	}
	{//test Thread QUeue with LOW_TEST threads
		cout<<"Starting test with "<<LOW_TEST<<" Threads"<<endl;
		cout<<"Creating initial Queue"<<endl;
		Merge_Queue<int> q;
		cout<<"Starting Mini TEST 1 "<<endl;

		thread monoTest[LOW_TEST];
		for(int i=0;i<LOW_TEST;i++){
			monoTest[i]=thread(count,10,q.registerThread());

		}

		bool fail=false;
		for(int i=0;i<10*LOW_TEST;i++){
				
			while(q.empty());

			if(q.top()!=i){
				fail=true;
			}
		}
	
			cout<<"\nMini test 1 passed"<<endl;

		cout<<"joining threads"<<endl;
		for(int i=0;i<LOW_TEST;i++){
			monoTest[i].join();
		}
}
{
Merge_Queue<int> q;
thread monoTest[LOW_TEST];
		cout<<"threading Mini Test 2"<<endl;
		for(int i=0;i<LOW_TEST;i++){
			monoTest[i]=thread(count,TEST_LEN,q.registerThread());

		}
cout<<"Starting Mini Test 2"<<endl;
		for(int i=0;i<TEST_LEN*LOW_TEST;i++){

			while(q.empty());
			q.pop();
		}
		cout<<"Mini test 2 passed"<<endl;
		for(int i=0;i<LOW_TEST;i++){
			monoTest[i].join();
		}
	}

		{//test Thread QUeue with HIGH_TEST threads
		cout<<"\nStarting test with "<<HIGH_TEST<<" Threads"<<endl;
		cout<<"Creating initial Queue"<<endl;
		Merge_Queue<int> q;
		cout<<"Starting Mega TEST 1 "<<endl;
		
		thread monoTest[HIGH_TEST];
		for(int i=0;i<HIGH_TEST;i++){
			monoTest[i]=thread(count,10,q.registerThread());

		}
		bool fail=false;
		for(int i=0;i<10*HIGH_TEST;i++){
				
			while(q.empty());

			if(q.top()!=i){
				fail=true;
			}
			
		}
	
			cout<<"\nMega test 1 passed"<<endl;

		cout<<"joining threads"<<endl;
		for(int i=0;i<HIGH_TEST;i++){
			monoTest[i].join();
		}
}
{
Merge_Queue<int> q;
thread monoTest[HIGH_TEST];
		cout<<"threading Mega Test 2"<<endl;
		for(int i=0;i<HIGH_TEST;i++){
			monoTest[i]=thread(count,TEST_LEN,q.registerThread());

		}
cout<<"Starting Mega Test 2"<<endl;
		for(int i=0;i<TEST_LEN*HIGH_TEST;i++){

			while(q.empty());
			q.pop();
		}
		cout<<"Mega test 2 passed"<<endl;
		for(int i=0;i<HIGH_TEST;i++){
			monoTest[i].join();
		}
	}
}
