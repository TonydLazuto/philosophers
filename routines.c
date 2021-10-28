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
	ft_usleep(phil->info->time_to_eat + 1);
	while (1)
	{
		usleep(500);
		if (!phil->last_meal)
			phil->last_meal = phil->start_time;
		if (get_current_time(phil->start_time) - phil->last_meal
				>= phil->info->time_to_die)
		{
			phil->info->someone_died = 1;
			print_msg(get_current_time(phil->start_time), phil->num, DIED);
			return (NULL);
		}
//		if (phil->nb_meals == 0)
//			;
//		if (get_current_time(phil->start_time) - phil->last_meal > phil->info->time_to_die / 2)
//			phil->starving = 1;
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo			*phil;
//	pthread_mutex_t	final;

	phil = (t_philo *)arg;
//	if (pthread_mutex_init(&final, NULL))
//		return (NULL);
	phil->start_time = get_time();
	phil->last_meal = 0;
	if (pthread_create(&phil->death, NULL, &death_routine, (void*)phil))
		return (NULL);
	if (pthread_detach(phil->death))
		return (NULL);
	if (!phil->right && !phil->left)
	{
		eat_alone(phil);
		return (NULL);
	}
/*
	while (!phil->info->someone_died)
	{
//		print_msg(get_current_time(phil->start_time), phil->num, " --> get_current_time\n", phil);
//		print_msg(phil->last_meal, phil->num, " ------> last_meal\n", phil);
		wait_for_eat(phil);
		sleeping(phil);
		thinking(phil);
	}
*/
//	while (phil->info->someone_died)
//		usleep(50);
/*
	pthread_mutex_lock(&final);
	phil = destroy_mutex(phil);
	if (!phil)
		return (NULL);
	pthread_mutex_unlock(&final);
	if (pthread_mutex_destroy(&final))
		return (NULL);
*/
	return (NULL);
}