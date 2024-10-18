/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:38:37 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/18 10:07:53 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

int	ft_isnbr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	pars_error(void)
{
	printf("Error: arguments must be numbers\n");
	exit(1);
}

void	print_philo(t_philo *philo)
{
	printf("philo_nbr: %d\n", philo->philo_nbr);
	printf("t_die: %d\n", philo->t_die);
	printf("t_eat: %d\n", philo->t_eat);
	printf("t_sleep: %d\n", philo->t_sleep);
	printf("meals_nbr: %d\n", philo->meals_nbr);
}
