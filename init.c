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
	return (phil);
}

int			init_mutex(t_philo **phil)
{
	t_philo		*cpy;

	cpy = *phil;
	while (cpy)
	{
		cpy->right_fork = malloc(sizeof(*cpy->right_fork));
		if (cpy->right_fork)
			return (-1);
		cpy->left_fork = malloc(sizeof(*cpy->left_fork));
		if (cpy->left_fork)
			return (-1);
		cpy->text = malloc(sizeof(*cpy->text));
		if (cpy->text)
			return (-1);
		if (pthread_mutex_init(cpy->right_fork, NULL))
			return (-1);
		if (pthread_mutex_init(cpy->left_fork, NULL))
			return (-1);
		if (pthread_mutex_init(cpy->text, NULL))
			return (-1);
		cpy = cpy->right;
	}
	return (0);
}

int			destroy_mutex(t_philo **phil, t_info info)
{
	int i;

	i = 0;
	while ((*phil)->left)
		*phil = (*phil)->left;
	while (i < info.nb_of_philos)
	{
/*		if (pthread_mutex_destroy((*phil)->right_fork))
			return (-1);
		if (pthread_mutex_destroy((*phil)->left_fork))
			return (-1);
*/
		if (pthread_mutex_destroy((*phil)->text))
			return (-1);
//		free((*phil)->right_fork);
//		free((*phil)->left_fork);
		free((*phil)->text);
		*phil = (*phil)->right;
		i++;
	}
	return (0);
}

t_philo		*link_forks(t_philo *phil)
{
	t_philo	*cpy;

	cpy = phil;
	while (cpy)
	{
		if (cpy->right)
			cpy->right_fork = cpy->right->left_fork;
		else
			cpy->right_fork = phil->left_fork;
		if (cpy->left)
			cpy->left_fork = cpy->left->right_fork;
		else
			cpy->left_fork = last_philo(phil)->right_fork;
		cpy = cpy->right;
	}
	return (phil);
}
