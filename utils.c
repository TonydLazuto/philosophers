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

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atoi(const char *str)
{
	long long	nb;

	nb = 0;
	while (*str == '\t' || *str == ' ' || *str == '0')
		str++;
	while (*str)
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return ((long)nb);
}

int		ft_strlen(const char *s)
{
	int	len;

	len = 0;
	if (s)
	{
		while (s[len])
			len++;
	}
	return (len);
}

/**
 * -----------------------------------------------
 */

long    get_time(long start_time)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000 ;
	return (milliseconds - start_time);
}
/*
void	ft_usleep(size_t time, long start_time)
{
	size_t	start;

	start = get_time(start_time);
	if (get_time(start_time) < time)
		usleep(100);
}
*/