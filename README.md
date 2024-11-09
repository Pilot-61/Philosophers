# Understanding Threads in C Programming

## Overview
A thread is the smallest unit of execution within a process. Often called "lightweight processes," threads share the same memory space of their parent process while running independently. This enables simultaneous task execution within a single program, enhancing efficiency and performance, particularly on multi-core processors.

## Table of Contents
1. [Basics of Threads](#basics-of-threads)
2. [POSIX Threads Library](#posix-threads-library)
3. [Creating a Thread](#creating-a-thread)
4. [Joining a Thread](#joining-a-thread)
5. [Synchronizing Threads](#synchronizing-threads)
6. [Terminating a Thread](#terminating-a-thread)
7. [Compiling a Threaded Program](#compiling-a-threaded-program)
8. [Example Program](#example-program)

## Basics of Threads
- Threads enable division of a process into multiple concurrent tasks
- They share the same memory and resources of the parent process
- Communication between threads is faster compared to inter-process communication

## POSIX Threads Library
- Uses the Pthreads library, standard on Unix-like systems
- Requires including `<pthread.h>`
- Must link with `-lpthread` when compiling

## Creating a Thread
Threads are created using the `pthread_create` function:

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
                  void *(*start_routine)(void *), void *arg);
```

### Parameters:
- `pthread_t *thread`: Pointer to store thread ID
- `const pthread_attr_t *attr`: Thread attributes (NULL for defaults)
- `void *(*start_routine)(void *)`: Function pointer for thread execution
- `void *arg`: Argument passed to thread function

### Basic Example:
```c
#include <pthread.h>
#include <stdio.h>

void *myThreadFunction(void *arg) {
    printf("Thread is running\n");
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, myThreadFunction, NULL);
    pthread_join(thread, NULL);
    return 0;
}
```

## Joining a Thread
Use `pthread_join` to wait for thread completion:

```c
int pthread_join(pthread_t thread, void **retval);
```

## Synchronizing Threads
Thread synchronization prevents race conditions when accessing shared resources.

### Mutex (Mutual Exclusion)
```c
pthread_mutex_t mutex;
pthread_mutex_init(&mutex, NULL);
pthread_mutex_lock(&mutex);
// critical section
pthread_mutex_unlock(&mutex);
pthread_mutex_destroy(&mutex);
```

### Condition Variables
```c
pthread_cond_t cond;
pthread_cond_init(&cond, NULL);
pthread_cond_wait(&cond, &mutex);    // Wait for condition
pthread_cond_signal(&cond);          // Signal waiting threads
pthread_cond_destroy(&cond);
```

## Terminating a Thread
Threads can terminate by:
- Returning from their start function
- Calling `pthread_exit`
- Being cancelled via `pthread_cancel`

## Compiling a Threaded Program
```bash
gcc myprogram.c -lpthread -o myprogram
```

## Example Program
Here's a complete example demonstrating thread creation, joining, and mutex synchronization:

```c
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;
int shared_counter = 0;

void *incrementCounter(void *arg) {
    pthread_mutex_lock(&mutex);
    shared_counter++;
    printf("Counter: %d\n", shared_counter);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread1, NULL, incrementCounter, NULL);
    pthread_create(&thread2, NULL, incrementCounter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);
    printf("Final Counter: %d\n", shared_counter);
    return 0;
}
```

## Key Points
- Threads are lightweight and share memory/resources with their parent process
- Pthreads provide comprehensive functions for thread management
- Proper synchronization is crucial for safe multithreading
- While threads add complexity, they can significantly improve performance through concurrency

## Note
Threading can significantly enhance program performance but requires careful implementation to avoid common pitfalls like race conditions and deadlocks. Always ensure proper synchronization when accessing shared resources.
