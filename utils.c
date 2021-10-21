/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:32:21 by aderose           #+#    #+#             */
/*   Updated: 2021/10/18 11:32:23 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long long	nb;

	nb = 0;
	while (*str == '\t' || *str == ' ' || *str == '0')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		nb = nb * 10 + *str - '0';
		str++;
	}
	return ((int)nb);
}
/**
 * -----------------------------------------------
 */
t_thread	*init(t_thread *th, t_info info)
{
	t_thread	*last;
	int			i;

	i = 0;
	while (i < info.nb_of_philos)
	{
		th = push_back(th, info, i + 1);
		if (!th)
			return (NULL);
		last = last_thread(th);
		pthread_mutex_init(&last->r_fork, NULL);
		i++;
	}
	return (th);
}


int		destroy_mutex(t_thread *th)
{
	int i;

	i = 0;
	while (i < th->info.nb_of_philos)
	{
		if (pthread_mutex_destroy(&th->r_fork))
			return (-1);
		i++;
	}
	return (0);
}

/**
 * -----------------------------------------------
 */
long    get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	ft_usleep(size_t time)
{
	size_t	start;

	start = get_time();
	if (get_time() - start < time)
		usleep(10000);
}
