/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:18:46 by aderose           #+#    #+#             */
/*   Updated: 2021/11/07 11:15:05 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutex(pthread_mutex_t *mut)
{
	if (pthread_mutex_destroy(mut))
		return ;
	free(mut);
	mut = NULL;
}

int	clear_philos(t_philo **phil, t_info *info)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&info->end))
		return (-1);
	if (pthread_mutex_destroy(&info->check_seats))
		return (-1);
	if (pthread_mutex_destroy(&info->status))
		return (-1);
	while (i < info->nb_of_philos)
	{
		free_mutex(phil[i]->right_fork);
		free_mutex(phil[i]->mut);
		phil[i]->left_fork = NULL;
		i++;
	}
	free(*phil);
	*phil = NULL;
	return (0);
}
