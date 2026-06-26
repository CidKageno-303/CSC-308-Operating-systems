#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define THREADS    5
#define INCREMENTS 100000
#define MAX_CONCURRENT 3   // counting semaphore: allow 3 threads at once

long counter = 0;
pthread_mutex_t mtx;
sem_t binary_sem;
sem_t counting_sem;

// ── approach 1: mutex ─────────────────────────────────
void *use_mutex(void *arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        pthread_mutex_lock(&mtx);
        counter++;
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

// ── approach 2: binary semaphore ─────────────────────
void *use_binary_sem(void *arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        sem_wait(&binary_sem);
        counter++;
        sem_post(&binary_sem);
    }
    return NULL;
}

// ── approach 3: counting semaphore (3 concurrent) ────
void *use_counting_sem(void *arg) {
    sem_wait(&counting_sem);
    printf("Thread %ld entered critical section\n", (long)arg);
    // simulate work
    for (volatile int i = 0; i < 1000000; i++);
    printf("Thread %ld leaving critical section\n", (long)arg);
    sem_post(&counting_sem);
    return NULL;
}

void run_approach(void *(*fn)(void*), const char *label) {
    pthread_t threads[THREADS];
    counter = 0;
    for (int i = 0; i < THREADS; i++)
        pthread_create(&threads[i], NULL, fn, (void*)(long)i);
    for (int i = 0; i < THREADS; i++)
        pthread_join(threads[i], NULL);
    long expected = (long)THREADS * INCREMENTS;
    printf("%s => Counter: %ld / %ld\n", label, counter, expected);
}

int main() {
    pthread_mutex_init(&mtx, NULL);
    sem_init(&binary_sem,   0, 1);
    sem_init(&counting_sem, 0, MAX_CONCURRENT);

    run_approach(use_mutex,      "Mutex          ");
    run_approach(use_binary_sem, "Binary Semaphore");

    // demonstrate counting semaphore
    printf("\n-- Counting Semaphore (max %d concurrent) --\n", MAX_CONCURRENT);
    pthread_t threads[THREADS];
    for (int i = 0; i < THREADS; i++)
        pthread_create(&threads[i], NULL, use_counting_sem, (void*)(long)i);
    for (int i = 0; i < THREADS; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&mtx);
    sem_destroy(&binary_sem);
    sem_destroy(&counting_sem);
    return 0;
}