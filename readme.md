# jalib
My personal library of usefull functions 
all the code here works for me in my use case, compatibility in your similar use case is not guarenteed
there may be "bad practices" in much of this, but to be honnest, I dont care what you call bad practices.
Half of bad practice is allowing the user to be an idiot if they want, but half of letting the user be an idiot
is giving the user power.  As the intended user is ME I want all the power I can get and trust my self not to be an idiot.

Thread Queues
A pair of queues for communicating with threads.  Both queues are guarenteed to be o(1) efficent (in general), non blocking , and thread safe.

Merge_queue
Inteneded to take "return" values from continually running threads and merge them for 1 thread
Guarenteed to be safe for n concurrent enqueu threads at the same as 1 dequeue thread
dequeue is o(1) usually, but can be o(N) if the queue is empty or close to empty.  To me, this is acceptable as if there is not much in the queue, there is not much for the thread to do anyway so it can afford to spend some time looking.

Split_Queue
Not strictly the oposite of Merge_Queue but close
Intended for 1 thread to issue instructions to all threads (ie broadcast messages to clients)
The Queue is a MISD modle and expects all threads to read the same data independently.
Guarenteed to be safe for n concurrent dequeue threads (they all get the same sequence) at the same tame as 1 enqueue thread 
