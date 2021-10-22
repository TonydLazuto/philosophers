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
	long	nb_meals;
}				t_info;

typedef struct s_thread
{
	int				num;
	pthread_t		pth;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;
	long			start_time;
	int				has_eaten;
	long			last_meal;
	struct s_thread	*left;
	struct s_thread	*right;
}				t_thread;

typedef struct s_global
{
	t_thread		*th;
	t_info			info;
	char			*buf;
}				t_global;

long		ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_strlen(const char *s);
int			check_args(int ac, char *av[]);

t_thread	*push_back(t_thread *list, int num);
t_thread	*last_thread(t_thread *elet);

int			init(char *av[], t_global *main);
int			destroy_mutex(t_global *main);
t_thread	*init_forks(t_thread *th);

long    	get_time(long start_time);
void		ft_usleep(size_t time, long start_time);

void		try_to_eat(t_global *main);
void		dying(t_global *main);
void		sleeping(t_global *main);
void		eating(t_global *main);
void		rest(t_global *main);
int			check_last_meal(t_global *main);

void  red();
void  blue();
void  green();
void  yellow();
void  reset();

# endif
