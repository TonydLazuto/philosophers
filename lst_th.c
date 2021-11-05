/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_th.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:18:46 by aderose           #+#    #+#             */
/*   Updated: 2021/10/19 17:19:04 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*new_philo(int num, t_info *info)
{
	t_philo	*elet;

	elet = (t_philo *)malloc(sizeof(*elet));
	if (!elet)
		return (NULL);
	elet->num = num;
	elet->nb_meals_eaten = 0;
	elet->info = info;
	elet->right_fork = NULL;
	elet->left_fork = NULL;
	elet->right = NULL;
	elet->left = NULL;
	return (elet);
}

t_philo	*last_philo(t_philo *elet)
{
	if (!elet)
		return (NULL);
	while (elet->right)
		elet = elet->right;
	return (elet);
}

void	push_back(t_philo **phil, int num, t_info *info)
{
	t_philo	*elet;
	t_philo	*tmp;

	tmp = NULL;
	elet = new_philo(num, info);
	if (!elet)
		return ;
	if (!*phil)
	{
		*phil = elet;
		return ;
	}
	tmp = last_philo(*phil);
	elet->left = tmp;
	tmp->right = elet;
}

t_philo	*pop_front(t_philo *phil)
{
	t_philo	*first;

	first = phil;
	if (!phil)
		return (NULL);
	phil = phil->right;
	free(first);
	first->right = NULL;
	first->left = NULL;
	first = NULL;
	if (phil)
		phil->left = NULL;
	return (phil);
}

int	clear_philos(t_philo **phil)
{
	while (*phil)
	{
		free_mutex((*phil)->right_fork);
		free_mutex((*phil)->mut);
		if (!*phil)
			return (-1);
		*phil = pop_front(*phil);
	}
	return (0);
}
