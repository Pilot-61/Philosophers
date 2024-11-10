/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 04:32:54 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/10 05:34:56 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

int	check_dead(t_data *data)
{
	int	is_dead;

	pthread_mutex_lock(&data->dead_mutex);
	is_dead = data->dead;
	pthread_mutex_unlock(&data->dead_mutex);
	return (is_dead);
}

void	check_take_fork(t_philo *philo, t_forks *first_fork, t_forks *sfork)
{
	pthread_mutex_lock(first_fork->forks);
	if (print_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(first_fork->forks);
		return ;
	}
	pthread_mutex_lock(sfork->forks);
	if (print_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(first_fork->forks);
		pthread_mutex_unlock(sfork->forks);
		return ;
	}
}

void	check_is_eating(t_philo *philo)
{
	if (print_status(philo, "is eating"))
	{
		pthread_mutex_unlock(philo->right_fork->forks);
		pthread_mutex_unlock(philo->left_fork->forks);
		return ;
	}
	my_usleep(philo->data->t_eat);
	pthread_mutex_lock(&philo->data->meals_mutex);
	philo->meals_count++;
	pthread_mutex_unlock(&philo->data->meals_mutex);
	pthread_mutex_unlock(philo->right_fork->forks);
	pthread_mutex_unlock(philo->left_fork->forks);
}

void	check_is_sleeping(t_philo *philo)
{
	if (print_status(philo, "is sleeping"))
		return ;
	my_usleep(philo->data->t_sleep);
}

void	set_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lastmmeal);
	philo->last_meal = mt();
	pthread_mutex_unlock(&philo->data->lastmmeal);
}
