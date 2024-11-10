/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:36:12 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/10 06:28:18 by mes-salh         ###   ########.fr       */
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
	long long	last_meal;
	t_forks		*left_fork;
	t_forks		*right_fork;
	pthread_t	thread_id;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	int				philo_nbr;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				meals_nbr;
	int				dead;
	long long		start;
	pthread_mutex_t	print;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	lastmmeal;
	pthread_mutex_t	meals_mutex;
	t_philo			*philo;
	t_forks			*forks;
	int				meals_completed;
	long long		current_time;
	long long		last_meal_time;
	long long		current_meals;
}	t_data;

int			ft_isnbr(char *str);
int			ft_atoi(char *str);
void		pars_error(void);
int			pars_values(t_data *data, char **av);
void		my_usleep(int time);
void		*safe_malloc(size_t size);
void		init(t_data *data);
long long	mt(void);
void		start_eating(t_data *data);
int			check_dead(t_data *data);
void		max_meals(t_data *data);
void		die(t_data *data, t_philo *philo);
void		set_last_meal(t_philo *philo);
void		check_is_sleeping(t_philo *philo);
void		check_is_eating(t_philo *philo);
void		check_take_fork(t_philo *philo, t_forks *first_fork,
				t_forks *second_fork);
int			check_dead(t_data *data);
int			print_status(t_philo *philo, char *status);
void		last_meal(t_data *data, t_philo *philo, int i);
void		lock_meals_mutex(t_data *data, int i);
#endif