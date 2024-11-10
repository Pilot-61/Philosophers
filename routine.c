/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 06:22:23 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/10 06:40:08 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

int	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print);
	if (check_dead(philo->data))
	{
		pthread_mutex_unlock(&philo->data->print);
		return (1);
	}
	printf("%lld %d %s\n", mt() - philo->data->start, philo->philo_id, status);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_forks	*first_fork;
	t_forks	*second_fork;

	philo = (t_philo *)arg;
	while (!check_dead(philo->data))
	{
		if (philo->philo_id % 2 == 0)
		{
			first_fork = philo->right_fork;
			second_fork = philo->left_fork;
		}
		else
		{
			first_fork = philo->left_fork;
			second_fork = philo->right_fork;
		}
		check_take_fork(philo, first_fork, second_fork);
		set_last_meal(philo);
		check_is_eating(philo);
		check_is_sleeping(philo);
		if (print_status(philo, "is thinking"))
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
		i = -1;
		data->meals_completed = 0;
		while (++i < data->philo_nbr)
		{
			last_meal(data, &data->philo[i], i);
			if (data->current_time - data->last_meal_time > data->t_die)
				return (die(data, &data->philo[i]), NULL);
			if (data->meals_nbr != -1)
			{
				lock_meals_mutex(data, i);
				if (data->current_meals >= data->meals_nbr)
					data->meals_completed++;
			}
			if (data->meals_nbr != -1
				&& data->meals_completed == data->philo_nbr)
				return (max_meals(data), NULL);
		}
		usleep(100);
	}
}

void	start_eating(t_data *data)
{
	int			i;
	pthread_t	death_thread;

	i = 0;
	if (data->philo_nbr == 1)
	{
		printf("%lld 1 has taken a fork\n", mt() - data->start);
		my_usleep(data->t_die);
		printf("%lld 1 died\n", mt() - data->start);
		return ;
	}
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
