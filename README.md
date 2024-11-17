# Philosophers 🍝

A project to solve the classic dining philosophers problem using threads and mutexes (or processes and semaphores for bonus).

## Overview

The dining philosophers problem is a classic computer science problem that illustrates synchronization issues and techniques for resolving them. The project simulates philosophers sitting at a round table doing three things:
- Eating 🍴
- Thinking 🤔
- Sleeping 😴

## Problem Description

- `n` philosophers sit at a round table with a large bowl of spaghetti in the middle
- There are `n` forks placed between each philosopher
- To eat, a philosopher needs to pick up both forks (left and right)
- After eating, philosophers put down their forks and start sleeping
- After sleeping, they start thinking
- The simulation stops when a philosopher dies or when all philosophers have eaten the required number of times

### Rules
- Philosophers don't speak with each other
- Philosophers don't know when another philosopher is about to die
- Philosophers must avoid dying!
- No global variables allowed

## Usage

### Compilation
```bash
# For mandatory part
cd philo
make
```

### Execution
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments
1. `number_of_philosophers`: Number of philosophers and forks
2. `time_to_die` (in ms): Maximum time since start of their last meal or the simulation before a philosopher dies
3. `time_to_eat` (in ms): Time it takes to eat (must hold two forks)
4. `time_to_sleep` (in ms): Time spent sleeping
5. `[number_of_times_each_philosopher_must_eat]` (optional): If specified, simulation stops when all philosophers eat at least this many times


### how to use the tester for mandatory
```bash
# Run all tests (500+)
./tester.sh

# Run basic test only
./tester.sh basic

# Run 50 random tests
./tester.sh random
```


## Implementation Details

### Mandatory Part (Using Threads)
- Each philosopher is a thread
- One fork between each pair of philosophers
- Forks are protected by mutexes
- Must avoid data races

Required External Functions:
- `memset`, `printf`, `malloc`, `free`, `write`
- `usleep`, `gettimeofday`
- `pthread_create`, `pthread_detach`, `pthread_join`
- `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`

### Bonus Part (Using Processes)
- Each philosopher is a process
- All forks are in the middle of the table
- Number of available forks is represented by a semaphore
- Main process should not be a philosopher

Additional External Functions for Bonus:
- `fork`, `kill`, `exit`
- `waitpid`
- `sem_open`, `sem_close`, `sem_post`, `sem_wait`, `sem_unlink`

## Logging

The program must log state changes with timestamps:
```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```
Where:
- `timestamp_in_ms` is the current timestamp in milliseconds
- `X` is the philosopher number

### Important Notes
- Messages should not be mixed up
- A death message should be displayed within 10ms of the actual death
- No data races are allowed

## Tips for Implementation

1. **Data Structure Design**
   - Create structures for philosophers and simulation data
   - Consider using a separate structure for forks/mutexes

2. **Time Management**
   - Use `gettimeofday()` for precise timing
   - Keep track of last meal time for each philosopher
   - Implement efficient sleep/wait mechanisms

3. **Death Checking**
   - Implement a monitoring system to check for deaths
   - Ensure quick death detection and reporting
   - Consider using a separate monitoring thread

4. **Resource Management**
   - Properly initialize and destroy mutexes/semaphores
   - Ensure proper memory management
   - Handle cleanup on program termination

5. **Testing Scenarios**
   ```bash
   # Basic test with 5 philosophers
   ./philo 5 800 200 200

   # Test with mandatory eating count
   ./philo 4 410 200 200 5

   # Edge cases
   ./philo 1 800 200 200
   ./philo 200 800 200 200
   ```

## Common Issues to Avoid

- Resource leaks (memory, mutexes, semaphores)
- Data races and deadlocks
- Delayed death detection
- Incorrect fork allocation/management
- Imprecise timing
- Mixed up logging messages

Remember: The goal is not just to make philosophers eat, but to create an efficient, race-free simulation that properly handles synchronization!

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
