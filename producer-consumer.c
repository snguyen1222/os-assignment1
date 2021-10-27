#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h> 

#define MAXITEMS 5 // Max number of items for produceer and consumer
#define BUFFERSIZE 5

sem_t empty; // counting semaphore whose initial value is the number of slows in the buffer
sem_t full; // counting semaphore whose initial value is 0

int buffer[BUFFERSIZE]; // Number of items in buffer
pthread_mutex_t mutex;
int nextIn = 0; // Index of next data of producer that will be produced
int nextOut = 0; // Index of next data of consumer that will be consumed

void* producer(void* p)
{
    int item;
    int i = 0;
    do {
        item = rand();
        sem_wait(&empty); // Wait until empty > 0 then decrement empty
        pthread_mutex_lock(&mutex); //Locks *mutex. caller is blocked until *mutex is unlocked and then &mutex is locked. Consumer cannot access until producer is done
        buffer[nextIn] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int*)p), buffer[nextIn], nextIn); // Add data to buffer
        nextIn = (nextIn + 1) % BUFFERSIZE;
        pthread_mutex_unlock(&mutex); // Release lock
        sem_post(&full); // Increment full
        i++;
    } while (i < MAXITEMS)
}
void* consumer(void* c)
{
    int i = 0;
    do {
        sem_wait(&full); // Wait until full > 0 and decrement full to consume data from the buffer
        pthread_mutex_lock(&mutex); // Acquire lock. Prevent producers from interrupting consumer
        int item = buffer[nextOut];
        printf("Consumer %d: Remove Item %d from %d\n", *((int*)c), item, nextOut); // Remove Data from buffer
        nextOut = (nextOut + 1) % BUFFERSIZE;
        pthread_mutex_unlock(&mutex); // Release lock
        sem_post(&empty); // Increment empty
        i++;
    } while (i < MAXITEMS)
}

void proconThread()
{
    for (int i = 0; i < 5; i++) {
        pthread_create(&pro[i], NULL, (void*)producer, (void*)&a[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_create(&con[i], NULL, (void*)consumer, (void*)&a[i]);
    }
}

void proconJoin()
{
    for (int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }
}

int main()
{
    pthread_t pro[5], con[5]; // Set Threads
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFERSIZE); // int sem_init(sem_t * sem, int pshared, unsigned int value); Initializes the semaphore *sem
    sem_init(&full, 0, 0);
    int a[5] = { 1,2,3,4,5 }; // Shows thread identity by tagging with a number on producer and consumer
    proconThread(); // Makes thread producer and consumer thread
    proconJoin(); // Main function exit prevention
    pthread_mutex_destroy(&mutex); // Removes pthread to prevent memory leak
    sem_destroy(&empty); // Memory leak prevention
    sem_destroy(&full); // Memory leak prevention
    return 0;
}