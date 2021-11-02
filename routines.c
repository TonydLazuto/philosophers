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
		pthread_mutex_lock(phil->mutex);
		if (get_current_time(phil->last_meal) >= phil->info->time_to_die)
		{
			pthread_mutex_lock(phil->info->status);
			phil->info->died = 1;
			print_msg(phil, DIED);
			pthread_mutex_unlock(phil->mutex);
			pthread_mutex_unlock(phil->info->status);
			pthread_mutex_unlock(phil->info->end);
			return (NULL);
		}
		pthread_mutex_unlock(phil->mutex);
		usleep(1000);
//		if (phil->nb_meals == 0)
//			;
//		if (get_current_time(phil->start_time) - phil->last_meal > phil->info->time_to_die / 2)
//			phil->starving = 1;
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo				*phil;
	pthread_t			death;

	phil = (t_philo *)arg;
	phil->last_meal = get_time();
	if (pthread_create(&death, NULL, &death_routine, arg))
		return (NULL);
	if (pthread_detach(death))
		return (NULL);
	while (!phil->info->died && phil->nb_meals_eaten < phil->info->nb_meals_to_eat)
	{
//		print_msg(get_current_time(phil->start_time), phil->num, " --> get_current_time\n", phil);
//		print_msg(phil->last_meal, phil->num, " ------> last_meal\n", phil);
		wait_for_eat(phil);
		eating(phil);
		sleeping(phil);
		thinking(phil);
	}
	pthread_mutex_lock(phil->info->update);
	phil->info->philos_seated--;
	pthread_mutex_unlock(phil->info->update);
	return (NULL);
}