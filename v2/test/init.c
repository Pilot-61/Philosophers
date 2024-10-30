/* ************************************************************************** */
/*                                                                            */
/*   init.c                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_data(t_data *data, int num_philos)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
    if (!data->forks)
        return (0);
    
    if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
        return (0);
    if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
        return (0);
    
    for (i = 0; i < num_philos; i++)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
            return (0);
    }
    
    data->dead = 0;
    data->start_time = 0;
    return (1);
}

int init_philosophers(t_philo **philos, t_data *data, int ac, char **av)
{
    int i;
    int num_philos;

    num_philos = ft_atoi(av[1]);
    *philos = malloc(sizeof(t_philo) * num_philos);
    if (!*philos)
        return (0);

    for (i = 0; i < num_philos; i++)
    {
        (*philos)[i].id = i + 1;
        (*philos)[i].num_philos = num_philos;
        (*philos)[i].time_to_die = ft_atoi(av[2]);
        (*philos)[i].time_to_eat = ft_atoi(av[3]);
        (*philos)[i].time_to_sleep = ft_atoi(av[4]);
        (*philos)[i].meals_eaten = 0;
        (*philos)[i].meals_required = (ac == 6) ? ft_atoi(av[5]) : -1;
        (*philos)[i].last_meal = 0;
        (*philos)[i].left_fork = &data->forks[i];
        (*philos)[i].right_fork = &data->forks[(i + 1) % num_philos];
        (*philos)[i].data = data;
        if (pthread_mutex_init(&(*philos)[i].meal_mutex, NULL) != 0)
            return (0);
    }
    return (1);
}