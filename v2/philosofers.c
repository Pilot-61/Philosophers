/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:38:34 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/30 16:49:20 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

int	main(int ac, char **av)
{
	t_data			*data;

	if (ac == 5 || ac == 6)
	{
		pars_values(data, av);
		// start_eating(data);
		// clean_table(data);
	}
	else
	{
		printf("Error: wrong number of arguments\n");
		exit(1);
	}
}
