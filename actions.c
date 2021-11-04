/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:17:14 by aderose           #+#    #+#             */
/*   Updated: 2021/10/18 11:17:15 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_starvation(t_philo *phil)
{
	if (phil->info->time_to_die > phil->info->time_to_eat * 2
			+ phil->info->time_to_sleep)
	{
//		printf("Special case\n");
		pthread_mutex_lock(phil->info->starv_zone);
		if (get_current_time(phil->info->start_time) - phil->last_meal
			== phil->info->time_to_eat + phil->info->time_to_sleep)
		{
//			printf("philo %d got more sleep, gluttony bastard\n", phil->num);
			ft_usleep(phil->info->time_to_eat);
		}
		pthread_mutex_unlock(phil->info->starv_zone);
	}
	
/**
 * 800 > 200*2 + 200
 **/
}

void	wait_for_eat(t_philo *phil)
{
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;

	l_fork = phil->left_fork;
	r_fork = phil->right_fork;
	if (phil->num % 2 == 0)
	{
		l_fork = phil->right_fork;
		r_fork = phil->left_fork;
	}
	check_starvation(phil);
	pthread_mutex_lock(l_fork);
	pthread_mutex_lock(phil->info->status);
	print_msg(phil, TAKEFORK);
	pthread_mutex_unlock(phil->info->status);
	pthread_mutex_lock(r_fork);
	pthread_mutex_lock(phil->mut);
	pthread_mutex_lock(phil->info->status);
	print_msg(phil, TAKEFORK);
	pthread_mutex_unlock(phil->info->status);
}

void	eating(t_philo *phil)
{	
	
	pthread_mutex_lock(phil->info->status);
	print_msg(phil, EATING);
	pthread_mutex_unlock(phil->info->status);
	phil->last_meal = get_current_time(phil->info->start_time);
	pthread_mutex_unlock(phil->mut);
	ft_usleep(phil->info->time_to_eat);
	pthread_mutex_unlock(phil->right_fork);
	pthread_mutex_unlock(phil->left_fork);
	phil->nb_meals_eaten++;
}

void	sleeping(t_philo *phil)
{
	pthread_mutex_lock(phil->info->status);
	print_msg(phil, SLEEPING);
	pthread_mutex_unlock(phil->info->status);
	ft_usleep(phil->info->time_to_sleep);
}

void	thinking(t_philo *phil)
{
	pthread_mutex_lock(phil->info->status);
	print_msg(phil, THINKING);
	pthread_mutex_unlock(phil->info->status);
}
