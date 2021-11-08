/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 08:30:17 by aderose           #+#    #+#             */
/*   Updated: 2021/10/22 08:30:18 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*link_left_fork(t_philo *phil, t_info *info, int i)
{
	if (info->nb_of_philos == 1)
	{
		phil[0].left_fork = NULL;
		return (phil);
	}
	if (i == 0){
		phil[0].left_fork = &phil[info->nb_of_philos - 1].right_fork;}
	else
		phil[i].left_fork = &phil[i - 1].right_fork;
	return (phil);
}

t_info	*init_mutexes(t_info *info)
{
	if (pthread_mutex_init(&info->end, NULL))
		return (NULL);
	if (pthread_mutex_init(&info->check_seats, NULL))
		return (NULL);
	if (pthread_mutex_init(&info->status, NULL))
		return (NULL);
	return (info);
}

t_info	*init_info(char *av[], t_info *info)
{
	info->nb_of_philos = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		info->nb_meals_to_eat = ft_atoi(av[5]);
	else
		info->nb_meals_to_eat = INT_MAX;
	info->philos_seated = info->nb_of_philos;
	info->died = 0;
	if (check_limits_values(info) == -1)
		return (NULL);
	info = init_mutexes(info);
	if (!info)
		return (NULL);
	return (info);
}

void	set_philo(t_philo *phil, t_info *info, int i)
{
	phil->info = info;
	phil->num = i + 1;
	phil->nb_meals_eaten = 0;
	phil->last_meal = 0;
	if (pthread_mutex_init(&phil->mut, NULL))
		return ;
	if (pthread_mutex_init(&phil->right_fork, NULL))
		return ;
}

t_philo	*init(char *av[], t_philo *philos, t_info *info)
{
	t_philo	phil[200];
	int		i;

	i = 0;

	info = init_info(av, info);
	if (!info)
		return (NULL);
	while (i < info->nb_of_philos)
	{
		set_philo(&phil[i], info, i);
		i++;
	}
	i = 0;
	while (i < info->nb_of_philos)
	{
		philos = link_left_fork(phil, info, i);
		i++;
	}
	return (philos);
}