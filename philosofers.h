/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:36:12 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/06 04:26:55 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOFERS_H
# define PHILOSOFERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <sys/errno.h>
# include <pthread.h>

typedef struct s_forks
{
	pthread_mutex_t	*forks;
	int				fork_id;
}	t_forks;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int			philo_id;
	int			meals_count;
	int			max_meals;
	int			last_meal;
	t_forks		*left_fork;
	t_forks		*right_fork;
	pthread_t	*thread_id;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	int		philo_nbr;
	long	t_die;
	long	t_eat;
	long	t_sleep;
	int		meals_nbr;
	int		start;
	int		end;
	t_philo	*philo;
	t_forks	*forks;
}	t_data;

int		ft_isnbr(char *str);
int		ft_atoi(char *str);
void	pars_error(void);
void	pars_values(t_data *data, char **av);
void	init_philo(t_philo *philo, char **av, int ac);
void	my_usleep(int time);
void	*safe_malloc(size_t size);
void	init(t_data *data);
#endif