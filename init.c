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

int			init_mutex(t_philo **phil)
{
	t_philo		*cpy;

	cpy = *phil;
	while (cpy)
	{
		cpy->right_fork = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
		if (!cpy->right_fork)
			return (-1);
		cpy->text = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
		if (!cpy->text)
			return (-1);
		if (pthread_mutex_init(cpy->right_fork, NULL))
			return (-1);
		if (pthread_mutex_init(cpy->text, NULL))
			return (-1);
		cpy = cpy->right;
	}
	return (0);
}

t_philo		*init(char *av[], t_philo *phil, t_info *info)
{
	int			i;
	long		nb_meals;

	i = 0;
	info->nb_of_philos = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		nb_meals = ft_atoi(av[5]);
	else
		nb_meals = 0;
	while (i < info->nb_of_philos)
	{
		push_back(&phil, i + 1, info, nb_meals);
		if (!phil)
			return (NULL);
		i++;
	}
	if (init_mutex(&phil) == -1)
		return (NULL);
	link_left_fork(&phil);
	return (phil);
}

int			destroy_mutex(t_philo *phil)
{
	if (pthread_mutex_destroy(phil->right_fork))
		return (-1);
	if (pthread_mutex_destroy(phil->text))
		return (-1);
	if (phil->right_fork)
		free(phil->right_fork);
	if (phil->text)
		free(phil->text);
	return (0);
}