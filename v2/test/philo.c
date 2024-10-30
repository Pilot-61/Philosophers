/* ************************************************************************** */
/*                                                                            */
/*   philosofers.c                                                           */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_data      data;
    t_philo     *philos;
    pthread_t   *threads;
    int         i;

    if (ac != 5 && ac != 6)
    {
        printf("Error: Invalid number of arguments\n");
        return (1);
    }
    if (!check_args(ac, av))
        return (1);

    if (!init_data(&data, ft_atoi(av[1])))
        return (1);
    if (!init_philosophers(&philos, &data, ac, av))
    {
        // Clean up data
        return (1);
    }

    // Create threads array
    threads = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
    if (!threads)
    {
        // Clean up everything
        return (1);
    }

    // Start simulation
    data.start_time = get_time();
    for (i = 0; i < ft_atoi(av[1]); i++)
    {
        if (pthread_create(&threads[i], NULL, philosopher_routine, &philos[i]))
        {
            // Handle error
            return (1);
        }
        usleep(100); // Prevent deadlock
    }

    // Monitor philosophers
    while (!check_death(philos))
        usleep(1000);

    // Clean up
    for (i = 0; i < ft_atoi(av[1]); i++)
        pthread_join(threads[i], NULL);

    // Free resources
    // ... (Add cleanup code)

    return (0);
}

void *philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        usleep(1000);

    while (!check_death(philo))
    {
        if (!take_forks(philo))
            break;
        if (!eat(philo))
            break;
        sleep_and_think(philo);
    }
    return (NULL);
}

int take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork");
    }
    return (1);
}

int eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->meal_mutex);
    
    print_status(philo, "is eating");
    my_usleep(philo->time_to_eat);
    
    philo->meals_eaten++;
    
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    
    return (1);
}

void sleep_and_think(t_philo *philo)
{
    print_status(philo, "is sleeping");
    my_usleep(philo->time_to_sleep);
    print_status(philo, "is thinking");
}