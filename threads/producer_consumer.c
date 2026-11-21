#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_QUEUE_SIZE 10
#define NUM_ITEMS 20

// Shared queue
int queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0, count = 0;

// Synchronization
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;

// Enqueue function (thread-safe)
void enqueue(int item) {
    pthread_mutex_lock(&lock);

    while (count == MAX_QUEUE_SIZE)
        pthread_cond_wait(&not_full, &lock);

    queue[rear] = item;
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    count++;

    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&lock);
}

// Dequeue function (thread-safe)
int dequeue() {
    pthread_mutex_lock(&lock);

    while (count == 0)
        pthread_cond_wait(&not_empty, &lock);

    int item = queue[front];
    front = (front + 1) % MAX_QUEUE_SIZE;
    count--;

    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&lock);

    return item;
}

// Producer thread function
void* producer(void* arg) {
    (void)arg;
    for (int i = 0; i < NUM_ITEMS; i++) {
        printf("Producing: %d\n", i);
        enqueue(i);
        usleep(100000); // simulate work
    }
    return NULL;
}

// Consumer thread function
void* consumer(void* arg) {
    (void)arg;
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = dequeue();
        printf("Consuming: %d\n", item);
        usleep(150000); // simulate work
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);

    return 0;
}
