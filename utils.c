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

static const char	*skip_space(const char *str)
{
	while (*str == '\t' || *str == ' ' || *str == '0')
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	long long	nb;

	nb = 0;
	str = skip_space(str);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		nb = nb * 10 + *str - '0';
		str++;
	}
	return ((int)nb);
}
