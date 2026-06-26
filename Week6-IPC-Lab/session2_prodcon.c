#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define ITEMS       10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t mutex_sem;   // binary: mutual exclusion
sem_t empty_sem;   // counts empty slots  (init = N)
sem_t full_sem;    // counts filled slots (init = 0)

void *producer(void *arg) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&empty_sem);          // wait for an empty slot
        sem_wait(&mutex_sem);          // enter critical section
        buffer[in] = i;
        printf("[Producer] Wrote: %d at slot %d\n", i, in);
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&mutex_sem);          // exit critical section
        sem_post(&full_sem);           // signal a filled slot
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&full_sem);           // wait for a filled slot
        sem_wait(&mutex_sem);          // enter critical section
        int item = buffer[out];
        printf("[Consumer] Read : %d from slot %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&mutex_sem);          // exit critical section
        sem_post(&empty_sem);          // signal an empty slot
        sleep(2);                      // consumer is slower
    }
    return NULL;
}

int main() {
    sem_init(&mutex_sem, 0, 1);
    sem_init(&empty_sem, 0, BUFFER_SIZE);
    sem_init(&full_sem,  0, 0);

    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&mutex_sem);
    sem_destroy(&empty_sem);
    sem_destroy(&full_sem);
    return 0;
}