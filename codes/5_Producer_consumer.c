#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores
sem_t empty;    // Counts empty slots
sem_t full;     // Counts filled slots
pthread_mutex_t mutex;  // To protect critical section

void* producer(void* arg) {
    int item = 1;
    while (1) {
        sem_wait(&empty);         // Wait if buffer is full
        pthread_mutex_lock(&mutex);

        // Critical section
        buffer[in] = item;
        printf("Producer produced: %d at %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;
        item++;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);          // Increase count of full slots

        sleep(1);  // Slow down for visibility
    }
}

void* consumer(void* arg) {
    while (1) {
        sem_wait(&full);          // Wait if buffer is empty
        pthread_mutex_lock(&mutex);

        // Critical section
        int item = buffer[out];
        printf("Consumer consumed: %d from %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);         // Increase count of empty slots

        sleep(2);  // Slow down for visibility
    }
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  
    sem_init(&full, 0, 0);           

    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Join threads (never ends)
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
