/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:38:34 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/06 04:25:30 by mes-salh         ###   ########.fr       */
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
	printf("r: %p\n", &philo.right_fork->fork_id);
	printf("l: %p\n", &philo.left_fork->fork_id);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		pars_values(&data, av);
		init(&data);
		for (int i = 0; i < data.philo_nbr; i++)
			print_data(&data, data.philo[i]);
		// start_eating(data);
		// clean_table(data);
		free(data.philo);
		free(data.forks);
	}
	else
	{
		printf("Error: wrong number of arguments\n");
		exit(1);
	}
}
