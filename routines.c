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
	ft_usleep(phil->info->time_to_eat + 2);
	while (1)
	{
//		ft_usleep(0.05);
		if (!phil->last_meal)
			phil->last_meal = phil->start_time;
		if (get_current_time(phil->start_time) - phil->last_meal
				>= phil->info->time_to_die)
		{
			phil->died = 1;
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
	t_philo				*phil;
	pthread_t			death;
	pthread_mutex_t		status;

	phil = (t_philo *)arg;
	if (pthread_mutex_init(&status, NULL))
		return (NULL);
	phil->start_time = get_time();
	if (pthread_create(&death, NULL, &death_routine, (void*)phil))
		return (NULL);
	if (pthread_detach(death))
		return (NULL);
	while (!phil->died)
	{
//		print_msg(get_current_time(phil->start_time), phil->num, " --> get_current_time\n", phil);
//		print_msg(phil->last_meal, phil->num, " ------> last_meal\n", phil);
		wait_for_eat(phil, &status);
		eating(phil, &status);
		sleeping(phil, &status);
		thinking(phil, &status);
	}
	if (pthread_mutex_destroy(&status))
		return (NULL);
	return (NULL);
}