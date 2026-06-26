#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_SIZE 1024
#define SEM_KEY  0x1234
#define SHM_KEY  0x5678

// semaphore helpers
void sem_op(int semid, int op) {
    struct sembuf sb = {0, op, 0};
    semop(semid, &sb, 1);
}

int main() {
    // Step 1: create shared memory segment
    int shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);

    // Step 2: attach in parent (will also attach in child after fork)
    char *shm = (char *)shmat(shmid, NULL, 0);

    // create semaphore for sync
    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    semctl(semid, 0, SETVAL, 0);  // init to 0 (child waits)

    pid_t pid = fork();

    if (pid == 0) {
        // ── CHILD: wait, then read ────────────────────────
        char *child_shm = (char *)shmat(shmid, NULL, 0);
        sem_op(semid, -1);  // Step 4: wait for parent signal
        printf("[Child]  Read from shared memory: \"%s\"\n", child_shm);
        // Step 5: detach
        shmdt(child_shm);
        exit(0);
    } else {
        // ── PARENT: write, then signal ────────────────────
        // Step 3: write data
        snprintf(shm, SHM_SIZE, "Hello from parent process! PID=%d", getpid());
        printf("[Parent] Wrote to shared memory : \"%s\"\n", shm);
        sem_op(semid, 1);   // Step 4: signal child to read
        wait(NULL);
        // Step 5: detach and remove
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
        printf("[Parent] Shared memory cleaned up.\n");
    }
    return 0;
}