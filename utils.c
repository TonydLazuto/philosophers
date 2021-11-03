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

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
}
