/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:38:34 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/18 10:07:50 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac == 5 || ac == 6)
	{
		if (ft_isnbr(av[1]) && ft_isnbr(av[2])
			&& ft_isnbr(av[3]) && ft_isnbr(av[4]))
		{
			philo.philo_nbr = ft_atoi(av[1]);
			philo.t_die = ft_atoi(av[2]);
			philo.t_eat = ft_atoi(av[3]);
			philo.t_sleep = ft_atoi(av[4]);
			philo.meals_nbr = -1;
			if (ac == 6)
			{
				if (ft_isnbr(av[5]))
					philo.meals_nbr = ft_atoi(av[5]);
				else
					pars_error();
			}
		}
		else
			pars_error();
	}
	print_philo(&philo);
	return (0);
}
