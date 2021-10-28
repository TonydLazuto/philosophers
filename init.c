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

void		link_left_fork(t_philo **phil)
{
	t_philo	*cpy;

	cpy = *phil;
	while (cpy)
	{
		if (!cpy->left && cpy->right)
			cpy->left_fork = last_philo(cpy)->right_fork;
		else
			cpy->left_fork = cpy->left->right_fork;
		cpy = cpy->right;
	}
}

t_philo		*init_mutex(t_philo *phil)
{
	t_philo		*cpy;

	cpy = phil;
	while (cpy)
	{
		cpy->right_fork = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
		if (!cpy->right_fork)
			return (NULL);
		if (pthread_mutex_init(cpy->right_fork, NULL))
			return (NULL);
		cpy = cpy->right;
	}
	return (phil);
}

t_philo		*init(char *av[], t_philo *phil, t_info *info)
{
	int			i;

	i = 0;
	info->nb_of_philos = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		info->nb_meals_to_eat = ft_atoi(av[5]);
	else
		info->nb_meals_to_eat = 0;
	info->someone_died = 0;
	while (i < info->nb_of_philos)
	{
		push_back(&phil, i + 1, info);
		if (!phil)
			return (NULL);
		i++;
	}
	phil = init_mutex(phil);
	if (!phil)
		return (NULL);
	if (phil->right)
		link_left_fork(&phil);
	return (phil);
}

t_philo		*destroy_mutex(t_philo *phil)
{
	pthread_mutex_unlock(phil->right_fork);
	if (pthread_mutex_destroy(phil->right_fork))
		return (NULL);
	return (phil);
}