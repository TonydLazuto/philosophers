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

# define COLOR_RESET   "\x1b[0m"
# define BOLDRED "\033[1m\033[31m"
# define BOLDGREEN "\033[1m\033[32m"
# define BOLDYELLOW "\033[1m\033[33m"
# define BOLDBLUE "\033[1m\033[34m"
# define BOLDMAGENTA "\033[1m\033[35m"
# define BOLDCYAN "\033[1m\033[36m"
# define BOLDWHITE "\033[1m\033[37m"

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
//	pthread_mutex_t	*end;
}				t_info;

typedef struct s_philo
{
	int				num;
	t_info			*info;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				died;
	long			nb_meals_eaten;
	long			start_time;
	long			last_meal;
	struct s_philo	*left;
	struct s_philo	*right;
}				t_philo;

long		ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_strlen(const char *s);
void		ft_free(char **s);
char		*ft_itoa(long nb);
void		ft_putstr(char *s);
void		superprint(char *time, char *num_phil, char *state);
void		print_msg(long timestamp, int num_philo,
				char *state);//, t_philo *phil);

int			check_args(int ac, char *av[]);
void		push_back(t_philo **phil, int num, t_info *info);
t_philo		*last_philo(t_philo *elet);
int			clear_philos(t_philo **phil);

t_philo		*init(char *av[], t_philo *phil, t_info *info);
t_philo		*destroy_mutex(t_philo *phil);

long		get_time(void);
void		ft_usleep(long time);
long		get_current_time(long start);

void		*death_routine(void *arg);
void		*routine(void *arg);
void		*observe(void *arg);

void		wait_for_eat(t_philo *main, pthread_mutex_t	*status);
void		eating(t_philo *phil, pthread_mutex_t	*status);
void		sleeping(t_philo *main, pthread_mutex_t	*status);
void		thinking(t_philo *main, pthread_mutex_t	*status);
//int		check_death(t_philo **phil, pthread_mutex_t *r_fork, pthread_mutex_t *l_fork);
void		eat_alone(t_philo *phil);

#endif
