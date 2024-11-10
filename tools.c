/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:38:37 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/10 07:39:00 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
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

void	init_times(t_data *data, char **av)
{
	data->philo_nbr = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
}

int	pars_values(t_data *data, char **av)
{
	init_times(data, av);
	if (ft_isnbr(av[1]) && ft_isnbr(av[2]) && ft_isnbr(av[3])
		&& ft_isnbr(av[4]))
	{
		if (data->t_die < 60 || data->t_eat < 60 || data->t_sleep < 60
			|| data->philo_nbr > 200 || data->philo_nbr <= 0)
			return (pars_error(), 1);
		if (av[5])
		{
			data->meals_nbr = ft_atoi(av[5]);
			if (data->meals_nbr < 1)
				return (pars_error(), 1);
		}
		else
			data->meals_nbr = -1;
		if (data->t_die > INT_MAX || data->t_eat > INT_MAX
			|| data->t_sleep > INT_MAX)
			return (pars_error(), 1);
		return (0);
	}
	return (1);
}
