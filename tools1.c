/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:39:41 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/10 04:38:53 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

long long	mt(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	my_usleep(int time)
{
	long long	start;

	start = mt();
	while (mt() - start < time)
		usleep(500);
}

void	die(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->print);
	printf("%lld %d died\n", mt() - data->start, philo->philo_id);
	pthread_mutex_unlock(&data->print);
	pthread_mutex_lock(&data->dead_mutex);
	data->dead = 1;
	pthread_mutex_unlock(&data->dead_mutex);
}

void	max_meals(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	data->dead = 1;
	pthread_mutex_unlock(&data->dead_mutex);
}
