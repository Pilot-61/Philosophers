/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:16:55 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/10 04:36:15 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

static void	init_forks(t_philo *philo, t_forks *forks, int i)
{
	int	philos;

	philos = philo->data->philo_nbr;
	philo->right_fork = &forks[i];
	philo->left_fork = &forks[(i + 1) % philos];
}

void	pthread_init(t_data *data)
{
	data->dead = 0;
	data->start = mt();
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->lastmmeal, NULL);
	data->philo = safe_malloc(sizeof(t_philo) * data->philo_nbr);
	data->forks = safe_malloc(sizeof(t_forks) * data->philo_nbr);
}

void	init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	pthread_init(data);
	while (++i < data->philo_nbr)
	{
		data->forks[i].forks = safe_malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(data->forks[i].forks, NULL);
		data->forks[i].fork_id = i;
	}
	i = -1;
	while (++i < data->philo_nbr)
	{
		philo = &data->philo[i];
		philo->philo_id = i + 1;
		philo->meals_count = 0;
		philo->last_meal = mt();
		philo->data = data;
		init_forks(philo, data->forks, i);
	}
}
