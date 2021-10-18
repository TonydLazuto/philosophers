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

#include <string.h>
#include <sys/time.h>
#include <pthread.h>

#include <errno.h>
#include <ctype.h>

enum e_action
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2
};

typedef struct s_arg
{
	int		nb_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		lunch_time;
}				t_arg;

typedef struct s_thread
{
	pthread_t		*th_id;
	char			*buf;
	int				num_thread;
	int				nb_philos_eating;
	int				nb_philos_thinking;
	int				nb_philos_sleeping;
}				t_thread;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		check_args(int ac, char *av[], t_arg *arg);

# endif
