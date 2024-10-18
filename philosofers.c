/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:38:34 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/18 10:43:13 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

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
