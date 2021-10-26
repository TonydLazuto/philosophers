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

t_philo	*new_philo(int num, t_info *info, long nb_meals)
{
	t_philo	*elet;

	elet = (t_philo *)malloc(sizeof(*elet));
	if (!elet)
		return (NULL);
	elet->num = num;
	elet->nb_meals = nb_meals;
	elet->info = info;
	elet->starving = 0;
	elet->last_meal = 0;
	elet->buf = NULL;
	elet->died = 0;
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

void	push_back(t_philo **list, int num,
						t_info *info, long nb_meals)
{
	t_philo	*elet;
	t_philo	*tmp;

	tmp = NULL;
	elet = new_philo(num, info, nb_meals);
	if (!elet)
		return ;
	if (!*list)
	{
		*list = elet;
		return ;
	}
	tmp = last_philo(*list);
	elet->left = tmp;
	tmp->right = elet;
}

t_philo	*pop_front(t_philo *list)
{
	t_philo	*first;

	first = list;
	if (!list)
		return (NULL);
	list = list->right;
	first->right = NULL;
	first->left = NULL;
	if (list)
		list->left = NULL;
	free(first);
	first = NULL;
	return (list);
}

int		clear_philos(t_philo **lst)
{
	if ((*lst)->left)
	{
		while ((*lst)->left)
			*lst = (*lst)->left;
	}
	while (*lst)
	{
		if (destroy_mutex(*lst) == -1)
			return (-1);
		*lst = pop_front(*lst);
	}
	return (0);
}
