/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:27:45 by aderose           #+#    #+#             */
/*   Updated: 2021/10/28 11:30:17 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*observe(void *arg)
{
	t_philo		*phil;
	t_philo		*first;

	phil = (t_philo *)arg;
	first = phil;
	while (phil)
	{
		if (phil->info->died)
		{
			pthread_mutex_lock(phil->info->status);
			print_msg(phil, DIED);
			pthread_mutex_unlock(phil->info->status);
			return (NULL);
		}
		phil = phil->right;
		if (!phil)
			phil = first;
	}
	return (NULL);
}
void	*death_routine(void *arg)
{
	t_philo		*phil;
	t_philo		*first;

	phil = (t_philo *)arg;
	first = phil;
	ft_usleep(phil->info->time_to_eat + 1);
	while (phil)
	{
		if (get_current_time(phil->info->start_time) - phil->last_meal >= phil->info->time_to_die)
		{
			phil->info->died = 1;
			while (1)
				usleep(100);
			return (NULL);
		}
		phil = phil->right;
		if (!phil)
			phil = first;
	}
	return (NULL);
}
/*
void	*meal_routine(void *arg)
{
	t_philo		*phil;
	t_philo		*first;

	phil = (t_philo *)arg;
	first = phil;
	while (phil)
	{
		if (phil->nb_meals_eaten >= phil->info->nb_meals_to_eat)
			phil->info->nb_finsh_eat--;
		phil = phil->right;
		if (!phil)
			phil = first;
	}
	return (NULL);
}
*/
void	*routine(void *arg)
{
	t_philo		*phil;

	phil = (t_philo *)arg;
//	while (!phil->info->died && phil->nb_meals_eaten < phil->info->nb_meals_to_eat)
	while (1)
	{
		wait_for_eat(phil);
		eating(phil);
		sleeping(phil);
		thinking(phil);
		if (phil->info->died)
		{
			printf("STOPPED\n");
			break ;
		}
	}
	return (NULL);
}
