/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 06:22:23 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/09 19:51:54 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d %s\n", mt() - philo->data->start, philo->philo_id, status);
	pthread_mutex_unlock(&philo->data->print);
}

int	check_dead(t_data *data)
{
	int	is_dead;

	pthread_mutex_lock(&data->dead_mutex);
	is_dead = data->dead;
	pthread_mutex_unlock(&data->dead_mutex);
	return (is_dead);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->philo_id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork->forks);
			if (check_dead(philo->data))
			{
				pthread_mutex_unlock(philo->left_fork->forks);
				return (NULL);
			}
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(philo->right_fork->forks);
			if (check_dead(philo->data))
			{
				pthread_mutex_unlock(philo->left_fork->forks);
				pthread_mutex_unlock(philo->right_fork->forks);
				return (NULL);
			}
			print_status(philo, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(philo->right_fork->forks);
			if (check_dead(philo->data))
			{
				pthread_mutex_unlock(philo->right_fork->forks);
				return (NULL);
			}
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(philo->left_fork->forks);
			if (check_dead(philo->data))
			{
				pthread_mutex_unlock(philo->left_fork->forks);
				pthread_mutex_unlock(philo->right_fork->forks);
				return (NULL);
			}
			print_status(philo, "has taken a fork");
		}
		print_status(philo, "is eating");
		philo->meals_count++;
		pthread_mutex_lock(&philo->data->lastmmeal);
		if (check_dead(philo->data))
		{
			pthread_mutex_unlock(&philo->data->lastmmeal);
			pthread_mutex_unlock(philo->left_fork->forks);
			pthread_mutex_unlock(philo->right_fork->forks);
			return (NULL);
		}
		philo->last_meal = mt();
		pthread_mutex_unlock(&philo->data->lastmmeal);
		my_usleep(philo->data->t_eat);
		pthread_mutex_unlock(philo->left_fork->forks);
		pthread_mutex_unlock(philo->right_fork->forks);
		if (check_dead(philo->data))
			return (NULL);
		print_status(philo, "is sleeping");
		my_usleep(philo->data->t_sleep);
		if (check_dead(philo->data))
			return (NULL);
		print_status(philo, "is thinking");
		if (check_dead(philo->data))
			return (NULL);
	}
	return (NULL);
}

void	*death_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			pthread_mutex_lock(&data->lastmmeal);
			if (mt() - data->philo[i].last_meal > data->t_die)
			{
				pthread_mutex_unlock(&data->lastmmeal);
				pthread_mutex_lock(&data->dead_mutex);
				data->dead = 1;
				pthread_mutex_unlock(&data->dead_mutex);
				print_status(&data->philo[i], "died");
				return (NULL);
			}
			pthread_mutex_unlock(&data->lastmmeal);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	start_eating(t_data *data)
{
	int			i;
	pthread_t	death_thread;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_create(&data->philo[i].thread_id, NULL,
			routine, &data->philo[i]);
		i++;
	}
	pthread_create(&death_thread, NULL, death_monitor, data);
	i = 0;
	pthread_join(death_thread, NULL);
	while (i < data->philo_nbr)
	{
		pthread_join(data->philo[i].thread_id, NULL);
		i++;
	}
}
