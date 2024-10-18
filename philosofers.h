/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:36:12 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/18 10:18:37 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOFERS_H
# define PHILOSOFERS_H
# include "libc.h"

typedef struct s_philo
{
	int	philo_nbr;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	meals_nbr;
}	t_philo;

int		ft_isnbr(char *str);
int		ft_atoi(char *str);
void	pars_error(void);
void	check_values(t_philo *philo);
void	print_philo(t_philo *philo);
#endif