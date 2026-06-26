# CSC 308 — Operating Systems 🖥️
## Department of Computer Science | Nnamdi Azikiwe University (UNIZIK)
Second Semester, 2025/2026 Academic Session
## 👤 Student Information
Field
Details
### Name
Chiadi Uchechukwu Paul
### Reg. No.
2023514221
### Department
Computer Science
### Level
300 Level
### Institution
Nnamdi Azikiwe University, Awka
### Course Code
CSC 308
### Course Title
Operating Systems

# 📁 Repository Structure
│
├── README.md
│
├── Week1-OS-Intro/
│   ├── docs/
│   │   └── CSC308_Week1_Answers.pdf
│   └── ...
│
└── Week6-IPC-Lab/
    ├── session1_mutex.c
    ├── session2_prodcon.c
    ├── session3_semaphore.c
    ├── session4_shm.c
    └── docs/
        └── CSC308_Week6_IPC_Lab.pngCSC 308 — Operating Systems 🖥️
# 📚 Assignment

## ✅ Week 6 — IPC, Process Synchronization & Shared Memory
Topics Covered: Mutex Locks, Semaphores, Producer-Consumer, Shared Memory
Session
Description
Source Code
Output
## Session 1
Mutex Lock Demonstration
session1_mutex.c

## Session 2
Producer-Consumer Simulation
session2_prodcon.c

## Session 3
Semaphore Implementation in C
session3_semaphore.c

## Session 4
Shared Memory Programming
session4_shm.c

# Key concepts covered:
Mutual exclusion using pthread_mutex_lock/unlock
Producer-Consumer problem using POSIX semaphores (sem_wait, sem_post)
Binary vs Counting semaphores
Inter-Process Communication (IPC) using shmget, shmat, shmdt, shmctl
Race conditions and how to eliminate them

# 🛠️ How to Compile & Run
All programs are written in C and tested on Linux (Ubuntu).
Requires gcc with pthread support.
Week 6 — IPC Lab
Bash

# 🔑 Key Functions Reference
| Function | Library | Purpose |
|----------|---------|---------|
| pthread_create() | pthread.h | Create a new thread |
| pthread_join() | pthread.h | Wait for thread to finish |
| pthread_mutex_lock() | pthread.h | Acquire mutex lock |
| pthread_mutex_unlock() | pthread.h | Release mutex lock |
| sem_init() | semaphore.h | Initialize a semaphore |
| sem_wait() | semaphore.h | Decrement semaphore (wait) |
| sem_post() | semaphore.h | Increment semaphore (signal) |
| shmget() | sys/shm.h | Create shared memory segment |
| shmat() | sys/shm.h | Attach shared memory |
| shmdt() | sys/shm.h | Detach shared memory |
| shmctl(IPC_RMID) | sys/shm.h | Destroy shared memory segment |

#📌 Notes
All lab outputs were verified and simulated on a Linux environment
Source code is fully commented for clarity
PDF documents contain detailed written answers to all theory questions
CSC 308 — Operating Systems | Nnamdi Azikiwe University | 2025/2026CSC 308 — Operating Systems 🖥️
Department of Computer Science | Nnamdi Azikiwe University (UNIZIK)
Second Semester, 2025/2026 Academic Session


