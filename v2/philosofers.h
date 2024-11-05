/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:36:12 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/05 20:14:54 by mes-salh         ###   ########.fr       */
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

typedef struct s_data t_data;

typedef struct s_philo
{
	int	philo_id;
	int	meals_count;
	int	max_meals;
	int	last_meal;
	t_forks	*left_fork;
	t_forks	*right_fork;
	pthread_t	*thread_id;
	t_data	*data;
}	t_philo;

typedef struct s_data
{
	int	philo_nbr;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	meals_nbr;
	int	start;
	int end;
	t_philo	*philo;
	t_forks	*forks;
}	t_data;

int		ft_isnbr(char *str);
int		ft_atoi(char *str);
void	pars_error(void);
void	pars_values(t_data *data, char **av);
void	init_philo(t_philo *philo, char **av, int ac);
void	my_usleep(int time);
void    *safe_malloc(size_t size);
void    safe_mutex_init(pthread_mutex_t *mutex);
void    safe_mutex_lock(pthread_mutex_t *mutex);
void    safe_mutex_unlock(pthread_mutex_t *mutex);
void    safe_mutex_destroy(pthread_mutex_t *mutex);
void    safe_thread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
void    safe_thread_join(pthread_t thread, void **retval);
void    safe_thread_detach(pthread_t thread);
void    init(t_data *data);
#endif