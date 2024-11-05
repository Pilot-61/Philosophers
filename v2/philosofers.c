/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:38:34 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/05 20:53:40 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

void print_data(t_data *data)
{
	printf("philo_nbr: %d\n", data->philo_nbr);
	printf("t_die: %d\n", data->t_die);
	printf("t_eat: %d\n", data->t_eat);
	printf("t_sleep: %d\n", data->t_sleep);
	printf("meals_nbr: %d\n", data->meals_nbr);
	printf("start: %d\n", data->philo->right_fork->fork_id);
	printf("start: %d\n", data->philo->left_fork->fork_id);
}

int	main(int ac, char **av)
{
	t_data			data;

	if (ac == 5 || ac == 6)
	{
		pars_values(&data, av);
		init(&data);
		// print_data(&data);
		// start_eating(data);
		// clean_table(data);
	}
	else
	{
		printf("Error: wrong number of arguments\n");
		exit(1);
	}
}
