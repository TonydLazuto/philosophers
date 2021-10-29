/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:13:19 by aderose           #+#    #+#             */
/*   Updated: 2021/10/26 14:13:21 by aderose          ###   ########.fr       */
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

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
}

void	print_msg(long timestamp, int num_philo, char *state, t_philo *phil)
{
	char	*time;
	char	*num_phil;

	num_phil = NULL;
	time = NULL;
	pthread_mutex_lock(phil->text);
	time = ft_itoa(timestamp);
	if (!time)
		return ;
	num_phil = ft_itoa((long)num_philo);
	if (!num_phil)
		return ;
	superprint(time, num_phil, state);	
	pthread_mutex_unlock(phil->text);
}
