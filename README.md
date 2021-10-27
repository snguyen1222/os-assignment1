# OS Producer Consumer Problem Assignment 1

Producer consumer problem is a classical synchronization problem. This problem is mainly solved by the uses of binary semaphores, counting semaphores, and mutual exclusion. This program uses these semaphores and mutex to solve the producer consumer problem:

* *sem_init()* -  initializes the semaphore *sem.
* *sem_wait(&empty)* - wait untill empty > 0 then decrement empty.
* *sem_post(&full)* - Increments full.
* *sem_post(&empty)* - Increments empty.
* *sem_destroy()* - Removes semaphores after usage to prevent memory leaks
* _pthread_mutex_t mutex_ - Mutex declaration.
* _pthread_mutex_lock(&mutex)_ - Locks *mutex. caller is blocked until *mutex is unlocked and then &mutex is locked. Consumer cannot access until producer is done.
* _pthread_mutex_unlock(&mutex)_ - Releases the lock.
* _pthread_mutex_init()_ - pthread initialization.
* *pthread_join()* - waits for the thread specified by thread to terminate.
* _pthread_mutex_destroy()_ - Removes mutex to prevent memory leak.

__To compile:__ gcc producer-consumer.c -pthread

__To run:__ ./a.out

# Used sources

http://faculty.cs.niu.edu/~hutchins/csci480/semaphor.htm

https://stackoverflow.com/questions/26623461/what-may-happen-if-sem-destroy-is-not-invoked-on-a-semaphore-in-c

https://www.youtube.com/watch?v=Qx3P2wazwI0

https://man7.org/linux/man-pages/man3/pthread_join.3.html