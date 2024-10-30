/* ************************************************************************** */
/*                                                                            */
/*   philosofers.h                                                           */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data
{
    pthread_mutex_t     *forks;
    pthread_mutex_t     write_mutex;
    pthread_mutex_t     death_mutex;
    int                 dead;
    long long           start_time;
} t_data;

typedef struct s_philo
{
    int             id;
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             meals_eaten;
    int             meals_required;
    long long       last_meal;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t meal_mutex;
    t_data          *data;
} t_philo;

// Time functions
long long   get_time(void);
void        my_usleep(int ms);

// Initialization
int         init_data(t_data *data, int num_philos);
int         init_philosophers(t_philo **philos, t_data *data, int ac, char **av);

// Philosopher actions
void        *philosopher_routine(void *arg);
int         take_forks(t_philo *philo);
int         eat(t_philo *philo);
void        sleep_and_think(t_philo *philo);

// Utility functions
int         ft_atoi(const char *str);
int         check_args(int ac, char **av);
void        print_status(t_philo *philo, char *status);
int         check_death(t_philo *philo);

#endif