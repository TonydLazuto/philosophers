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

void	*observe(void *data)
{
	t_info		*info;

	info = (t_info *)data;
	while (!info->died && info->philos_seated > 0)
		usleep(100);
	if (info->died)
		return (NULL);
	pthread_mutex_unlock(info->end);
	return (NULL);
}

void	*death_routine(void *data)
{
	t_philo		*phil;

	phil = (t_philo *)data;
	while (!phil->info->died && phil->nb_meals_eaten < phil->info->nb_meals_to_eat)
	{
		pthread_mutex_lock(phil->mut);
		if (get_current_time(phil->info->start_time) - phil->last_meal
				>= phil->info->time_to_die)
		{
			pthread_mutex_lock(phil->info->status);
			print_msg(phil, DIED);
			phil->info->died = 1;
			pthread_mutex_unlock(phil->info->status);
			pthread_mutex_unlock(phil->mut);
			pthread_mutex_unlock(phil->info->end);
			return (NULL);
		}
		pthread_mutex_unlock(phil->mut);
	}
//	printf("Gone from death routine\n");
	return (NULL);
}

void	*routine(void *data)
{
	t_philo		*phil;
	pthread_t	death;

	phil = (t_philo *)data;
	phil->last_meal = 0;
	if (pthread_create(&death, NULL, &death_routine, data))
	  	return (NULL);
	if (pthread_detach(death))
	  	return (NULL);
	while (!phil->info->died && phil->nb_meals_eaten
			< phil->info->nb_meals_to_eat)
	{
		wait_for_eat(phil);
		eating(phil);
		sleeping(phil);
		thinking(phil);
	}
	pthread_mutex_lock(phil->info->check_seats);
	phil->info->philos_seated--;
	pthread_mutex_unlock(phil->info->check_seats);
	return (NULL);
}