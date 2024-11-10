/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:38:34 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/10 05:23:32 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

void	print_data(t_data *data, t_philo philo)
{
	printf("philo_nbr: %d\n", data->philo_nbr);
	printf("t_die: %ld\n", data->t_die);
	printf("t_eat: %ld\n", data->t_eat);
	printf("t_sleep: %ld\n", data->t_sleep);
	printf("meals_nbr: %d\n", data->meals_nbr);
	printf("id: %d\n", philo.philo_id);
	printf("r: %d\n", philo.right_fork->fork_id);
	printf("l: %d\n", philo.left_fork->fork_id);
}

void	clean_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
		pthread_mutex_destroy(data->forks[i].forks);
	free(data->forks);
	free(data->philo);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead_mutex);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		pars_values(&data, av);
		init(&data);
		start_eating(&data);
		clean_data(&data);
	}
	else
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	return (0);
}
