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

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# include <errno.h>
# include <ctype.h>

# define TAKEFORK " has taken a fork\n"
# define EATING " is eating\n"
# define SLEEPING " is sleeping\n"
# define THINKING " is thinking\n"
# define DIED " died\n"

typedef struct s_info
{
	long			nb_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_meals_to_eat;
	long			start_time;
	long			philos_seated;
	int				died;
	pthread_mutex_t	end;
	pthread_mutex_t	check_seats;
	pthread_mutex_t	status;
}				t_info;

typedef struct s_philo
{
	int				num;
	t_info			*info;
	pthread_mutex_t	*mut;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	long			nb_meals_eaten;
	long			last_meal;
	struct s_philo	*left;
	struct s_philo	*right;
}				t_philo;

long		ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_strlen(const char *s);
char		*ft_itoa(long nb, char *s);
void		ft_putstr(char *s);
int			ft_strlcpy(char *dst,
				const char *src, int dstsize);
char		*ft_strcat(char *dst, const char *src);
void		print_msg(t_philo *phil, char *state);

int			check_args(int ac, char *av[]);
int			check_info(t_info *info);
void		push_back(t_philo **phil, int num, t_info *info);
t_philo		*last_philo(t_philo *elet);
int			clear_philos(t_philo **phil);

t_philo		*init(char *av[], t_philo *phil, t_info *info);
void		free_mutex(pthread_mutex_t *mut);

long		get_time(void);
void		ft_usleep(long time);
long		get_current_time(long start);

void		*death_routine(void *data);
void		*routine(void *data);
void		*observe(void *data);

void		wait_for_eat(t_philo *phil);
void		eating(t_philo *phil);
void		sleeping(t_philo *phil);
void		thinking(t_philo *phil);
void		eat_alone(t_philo *phil);

#endif
