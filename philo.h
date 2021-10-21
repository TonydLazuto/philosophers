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

typedef struct s_info
{
	int		nb_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		lunch_time;
}				t_info;

typedef struct s_thread
{
	t_info			*info;
	pthread_t		pth;
	pthread_mutex_t	r_fork;
	int				has_eaten;
	long			last_meal;
	int				num;
	char			*buf;
	struct s_thread	*left;
	struct s_thread	*right;
}				t_thread;

int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			check_args(int ac, char *av[], t_info *info);
int			init(t_thread **pth, t_info info);
int			destroy_mutex(t_thread *pth);
long    	get_time(void);
void		ft_usleep(size_t time);
t_thread	*push_back(t_thread *list, t_info *info, int num);
t_thread	*last_thread(t_thread *elet);

# endif
