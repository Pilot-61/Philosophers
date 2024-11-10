/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 05:46:46 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/10 06:26:56 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

void	last_meal(t_data *data, t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->lastmmeal);
	data->last_meal_time = data->philo[i].last_meal;
	data->current_time = mt();
	pthread_mutex_unlock(&philo->data->lastmmeal);
}

void	lock_meals_mutex(t_data *data, int i)
{
	pthread_mutex_lock(&data->meals_mutex);
	data->current_meals = data->philo[i].meals_count;
	pthread_mutex_unlock(&data->meals_mutex);
}

void	pars_error(void)
{
	printf("Error: arguments must be numbers\n");
	printf("Error: time must be more than 60ms and less than INT_MAX\n");
}
