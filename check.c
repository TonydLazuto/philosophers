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

int		check_nb_philos(const char *av, t_info *info)
{
	info->nb_of_philos = ft_atoi(av);
	if (info->nb_of_philos < 1)
		return (-1);
	if (ft_strlen(av) > ft_strlen("2147483647") || 
		ft_atoi(av) <= 0 || ft_atoi(av) > INT_MAX)
		return (-1);
	return (0);
}

int		check_time_to_die(const char *av, t_info *info)
{
	info->time_to_die = ft_atoi(av);
	if (info->time_to_die < 1)
		return (-1);
	if (ft_strlen(av) > ft_strlen("2147483647") || 
		ft_atoi(av) <= 0 || ft_atoi(av) > INT_MAX)
		return (-1);
	return (0);
}

int		check_time_to_eat(const char *av, t_info *info)
{
	info->time_to_eat = ft_atoi(av);
	if (info->time_to_eat < 1)
		return (-1);
	if (ft_strlen(av) > ft_strlen("2147483647") || 
		ft_atoi(av) <= 0 || ft_atoi(av) > INT_MAX)
		return (-1);
	return (0);
}

int		check_time_to_sleep(const char *av, t_info *info)
{
	info->time_to_sleep = ft_atoi(av);
	if (info->time_to_sleep < 1)
		return (-1);
	if (ft_strlen(av) > ft_strlen("2147483647") || 
		ft_atoi(av) <= 0 || ft_atoi(av) > INT_MAX)
		return (-1);
	return (0);
}

int		check_args(int ac, char *av[], t_info *info)
{
	if (ac != 5 && ac != 6)
		return (-1);
	if (check_nb_philos(av[1], info) == -1)
		return (-1);
	if (check_time_to_die(av[2], info) == -1)
		return (-1);
	if (check_time_to_eat(av[3], info) == -1)
		return (-1);
	if (check_time_to_sleep(av[4], info) == -1)
		return (-1);
	if (av[5])
	{
		info->lunch_time = ft_atoi(av[5]);
		if (ft_strlen(av) > ft_strlen("2147483647") || 
			ft_atoi(av) <= 0 || ft_atoi(av) > INT_MAX)
			return (-1);
		if (info->lunch_time == -1)
			return (-1);
		if (info->lunch_time < 1)
			return (-1);
		return (0);
	}
	else
		info->lunch_time = 0;
	return (0);
}