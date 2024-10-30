/* ************************************************************************** */
/*                                                                            */
/*   utils.c                                                                  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_time(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void print_status(t_philo *philo, char *status)
{
    pthread_mutex_lock(&philo->data->write_mutex);
    if (!check_death(philo))
    {
        printf("%lld %d %s\n",
            get_time() - philo->data->start_time,
            philo->id,
            status);
    }
    pthread_mutex_unlock(&philo->data->write_mutex);
}

int check_death(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->death_mutex);
    if (philo->data->dead)
    {
        pthread_mutex_unlock(&philo->data->death_mutex);
        return (1);
    }
    
    pthread_mutex_lock(&philo->meal_mutex);
    if (philo->last_meal != 0 && 
        (get_time() - philo->last_meal) > philo->time_to_die)
    {
        pthread_mutex_lock(&philo->data->write_mutex);
        printf("%lld %d died\n",
            get_time() - philo->data->start_time,
            philo->id);
        philo->data->dead = 1;
        pthread_mutex_unlock(&philo->data->write_mutex);
        pthread_mutex_unlock(&philo->meal_mutex);
        pthread_mutex_unlock(&philo->data->death_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->meal_mutex);
    pthread_mutex_unlock(&philo->data->death_mutex);
    return (0);
}
int	ft_isnbr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int check_args(int ac, char **av)
{
    int i;

    if (ac < 5 || ac > 6)
        return (0);
    
    // Skip av[0] (program name)
    for (i = 1; i < ac; i++)
    {
        if (!ft_isnbr(av[i]))
            return (0);
        if (ft_atoi(av[i]) <= 0)
            return (0);
    }

    // Additional specific checks
    if (ft_atoi(av[1]) > 200)  // Max philosophers
        return (0);
    if (ft_atoi(av[2]) < 60)   // Min time to die
        return (0);
    if (ft_atoi(av[3]) < 60)   // Min time to eat
        return (0);
    if (ft_atoi(av[4]) < 60)   // Min time to sleep
        return (0);
    
    return (1);
}
