/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:33 by aderose           #+#    #+#             */
/*   Updated: 2021/10/26 14:12:34 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;
	long			milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = tv.tv_sec * 1000;
	milliseconds += tv.tv_usec / 1000;
	return (milliseconds);
}

void	ft_usleep(long long time)
{
	long long	start;

	start = get_time();
	while (1)
	{
		if (get_time() - start >= time)
			break ;
		usleep(200);
	}
}

long long	get_current_time(long long start)
{
	return (get_time() - start);
}
