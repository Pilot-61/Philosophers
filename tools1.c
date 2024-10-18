/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:39:41 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/18 10:45:00 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	my_usleep(int time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

void	init_philo(t_philo *philo, char **av, int ac)
{
	if (ac == 5 || ac == 6)
	{
		if (ft_isnbr(av[1]) && ft_isnbr(av[2]) && ft_isnbr(av[3])
			&& ft_isnbr(av[4]))
		{
			philo->philo_nbr = ft_atoi(av[1]);
			philo->t_die = ft_atoi(av[2]);
			philo->t_eat = ft_atoi(av[3]);
			philo->t_sleep = ft_atoi(av[4]);
			if (ac == 6 && ft_isnbr(av[5]))
				philo->meals_nbr = ft_atoi(av[5]);
			else
				philo->meals_nbr = -1;
			check_values(philo);
		}
		else
			pars_error();
	}
}
