#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

// Define philosopher structure
typedef struct s_philosopher {
    int id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
} t_philosopher;

// Function to get the current timestamp in milliseconds
long get_timestamp(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

// Function for the philosopher's routine
void *philosopher_routine(void *arg) {
    t_philosopher *philosopher = (t_philosopher *)arg;

    // Philosopher starts thinking
    printf("%ld ms Philosopher %d is thinking\n", get_timestamp(), philosopher->id);

    while (1) {
        // Philosopher picks up forks
        pthread_mutex_lock(philosopher->left_fork);
        printf("%ld ms Philosopher %d has taken the left fork\n", get_timestamp(), philosopher->id);
        
        pthread_mutex_lock(philosopher->right_fork);
        printf("%ld ms Philosopher %d has taken the right fork\n", get_timestamp(), philosopher->id);

        // Philosopher starts eating
        printf("%ld ms Philosopher %d is eating\n", get_timestamp(), philosopher->id);
        usleep(philosopher->time_to_eat * 1000);  // Simulate eating

        // Philosopher puts down forks
        pthread_mutex_unlock(philosopher->right_fork);
        pthread_mutex_unlock(philosopher->left_fork);

        // Philosopher starts sleeping
        printf("%ld ms Philosopher %d is sleeping\n", get_timestamp(), philosopher->id);
        usleep(philosopher->time_to_sleep * 1000);  // Simulate sleeping

        // Philosopher starts thinking again
        printf("%ld ms Philosopher %d is thinking\n", get_timestamp(), philosopher->id);
    }
    return NULL;
}

int main(int argc, char **argv) {
    if (argc < 5) {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep\n", argv[0]);
        return 1;
    }

    // Parse command-line arguments
    int number_of_philosophers = atoi(argv[1]);
    long time_to_die = atol(argv[2]);
    long time_to_eat = atol(argv[3]);
    long time_to_sleep = atol(argv[4]);

    // Special case: handle one philosopher
    if (number_of_philosophers == 1) {
        printf("%ld ms Philosopher 1 has taken the left fork\n", get_timestamp());
        usleep(time_to_die * 1000);  // Simulate waiting for death
        printf("%ld ms Philosopher 1 died\n", get_timestamp());
        return 0;
    }

    // Create philosophers and forks
    pthread_mutex_t forks[number_of_philosophers];
    t_philosopher philosophers[number_of_philosophers];
    pthread_t threads[number_of_philosophers];

    // Initialize mutexes for forks
    for (int i = 0; i < number_of_philosophers; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < number_of_philosophers; i++) {
        philosophers[i].id = i + 1;
        philosophers[i].left_fork = &forks[i];
        philosophers[i].right_fork = &forks[(i + 1) % number_of_philosophers];
        philosophers[i].time_to_die = time_to_die;
        philosophers[i].time_to_eat = time_to_eat;
        philosophers[i].time_to_sleep = time_to_sleep;

        pthread_create(&threads[i], NULL, philosopher_routine, &philosophers[i]);
    }

    // Wait for philosopher threads to finish
    for (int i = 0; i < number_of_philosophers; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < number_of_philosophers; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
