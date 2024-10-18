/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:38:34 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/18 10:25:00 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

void	init_philo(t_philo *philo, char **av, int ac)
{
	if (ac == 5 || ac == 6)
	{
		philo->philo_nbr = ft_atoi(av[1]);
		philo->t_die = ft_atoi(av[2]);
		philo->t_eat = ft_atoi(av[3]);
		philo->t_sleep = ft_atoi(av[4]);
		philo->meals_nbr = -1;
		if (ac == 6)
		{
			if (ft_isnbr(av[5]))
				philo->meals_nbr = ft_atoi(av[5]);
			else
				pars_error();
		}
		check_values(philo);
	}
}

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac < 5 || ac > 6)
	{
		printf("Error: wrong number of arguments\n");
		exit(1);
	}
	init_philo(&philo, av, ac);
	print_philo(&philo);
	return (0);
}
