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

void	*death_routine(void *arg)
{
	t_philo		*phil;

	phil = (t_philo *)arg;
	while (!phil->info->died && phil->nb_meals_eaten < phil->info->nb_meals_to_eat)
	{
		if (get_current_time(phil->last_meal) >= phil->info->time_to_die)
		{
			pthread_mutex_lock(phil->info->status);
			phil->info->died = 1;
			print_msg(phil, DIED);
			pthread_mutex_unlock(phil->info->status);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo				*phil;
//	pthread_t			death;

	phil = (t_philo *)arg;
	phil->last_meal = 0;
	// if (pthread_create(&death, NULL, &death_routine, arg))
	// 	return (NULL);
	// if (pthread_detach(death))
	// 	return (NULL);

	// while (!phil->info->died && phil->nb_meals_eaten < phil->info->nb_meals_to_eat)
	while (1)
	{
		wait_for_eat(phil);
		eating(phil);
		sleeping(phil);
		thinking(phil);
	}
	return (NULL);
}