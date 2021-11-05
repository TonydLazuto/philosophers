/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:25:19 by aderose           #+#    #+#             */
/*   Updated: 2021/10/18 11:25:20 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char *av[])
{
	int		i;
	int		j;

	i = 1;
	if (ac != 5 && ac != 6)
		return (-1);
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (-1);
			j++;
		}
		if (ft_strlen(av[i]) > ft_strlen("2147483647")
			|| ft_atoi(av[i]) < 1 || ft_atoi(av[i]) > INT_MAX)
			return (-1);
		i++;
	}
	return (0);
}
