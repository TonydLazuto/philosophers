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

t_thread	*new_nb(t_info *info)
{
	t_thread	*elet;

	elet = (t_thread *)malloc(sizeof(*elet));
	if (!elet)
		return (NULL);
	elet->buf = NULL;
	elet->info = info;
	elet->right = NULL;
	elet->left = NULL;
	return (elet);
}

t_thread	*last_thread(t_thread *elet)
{
	if (!elet)
		return (NULL);
	while (elet->right)
		elet = elet->right;
	return (elet);
}

t_thread	*push_back(t_thread *list, t_info *info)
{
	t_thread	*elet;
	t_thread	*tmp;

	elet = new_nb(info);
	tmp = list;
	if (!elet)
		return (NULL);
	if (!list)
		return (elet);
	tmp = last_thread(tmp);
	elet->left = tmp;
	tmp->right = elet;
	return (list);
}

t_thread	*pop_front(t_thread *list)
{
	t_thread	*first;

	first = list;
	if (!list)
		return (NULL);
	list = list->right;
	first->right = NULL;
	free(first);
	first = NULL;
	return (list);
}

void	clear_lst(t_thread **lst)
{
	while (*lst)
		*lst = pop_front(*lst);
}
