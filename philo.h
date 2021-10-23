/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:47:08 by aderose           #+#    #+#             */
/*   Updated: 2021/10/14 18:47:42 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# include <errno.h>
# include <ctype.h>

typedef struct s_info
{
	long	nb_of_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
}				t_info;

typedef struct s_philo
{
	int				num;
	t_info			*info;
	char			*buf;
	pthread_t		pth;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	text;
	long			nb_meals;
	long			start_time;
	int				has_eaten;
	long			last_meal;
	struct s_philo	*left;
	struct s_philo	*right;
}				t_philo;

long		ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_strlen(const char *s);
int			check_args(int ac, char *av[]);

void		push_back(t_philo **list, int num,
						t_info *info, long nb_meals);
t_philo		*last_philo(t_philo *elet);
void		clear_philos(t_philo **lst);

t_philo		*init(char *av[], t_philo *phil, t_info *info);
int			destroy_mutex(t_philo **phil, t_info info);
t_philo		*link_forks(t_philo *th);

long    	get_time();
void		ft_usleep(long time);

void		try_to_eat(t_philo *main);
void		eating(t_philo *phil);
void		sleeping(t_philo *main);
void		thinking(t_philo *main);
void		rest(t_philo *main);
int			check_last_meal(t_philo *main);

void  red();
void  blue();
void  green();
void  yellow();
void  reset();

# endif
