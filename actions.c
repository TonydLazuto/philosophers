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
/*
int		check_death(t_philo **phil, pthread_mutex_t *r_fork,
			pthread_mutex_t *l_fork)
{
	ft_usleep(0.005);
	if ((*phil)->info->someone_died)
	{
		if (r_fork)
		{
			pthread_mutex_unlock((*phil)->right_fork);
			(*phil)->right_fork = NULL;

		}
		if (l_fork)
		{
			pthread_mutex_unlock((*phil)->left_fork);
			(*phil)->left_fork = NULL;
		}
		return (1);
	}
	return (0);
}
*/
void	wait_for_eat(t_philo *phil)
{
	if (phil->num % 2)
	{
		pthread_mutex_lock(phil->left_fork);
		pthread_mutex_lock(phil->info->status);
		print_msg(phil, TAKEFORK);
		pthread_mutex_unlock(phil->info->status);
		pthread_mutex_lock(phil->right_fork);
//		pthread_mutex_lock(phil->mutex);
		pthread_mutex_lock(phil->info->status);
		print_msg(phil, TAKEFORK);
		pthread_mutex_unlock(phil->info->status);
	}
	else
	{
		pthread_mutex_lock(phil->right_fork);
		pthread_mutex_lock(phil->info->status);
		print_msg(phil, TAKEFORK);
		pthread_mutex_unlock(phil->info->status);
		pthread_mutex_lock(phil->left_fork);
//		pthread_mutex_lock(phil->mutex);
		pthread_mutex_lock(phil->info->status);
		print_msg(phil, TAKEFORK);
		pthread_mutex_unlock(phil->info->status);
	}
}

void	eating(t_philo *phil)
{	
//	print_msg(get_current_time(phil->start_time), phil->num, " --> get_current_time()\n", phil);
//	print_msg(phil->info->time_to_eat, phil->num, " --> time_to_eat\n", phil);
//	pthread_mutex_lock(phil->mutex);
	phil->last_meal = get_current_time(phil->info->start_time);
	pthread_mutex_lock(phil->info->status);
	print_msg(phil, EATING);
	pthread_mutex_unlock(phil->info->status);
	ft_usleep(phil->info->time_to_eat);
//	pthread_mutex_unlock(phil->mutex);
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
	usleep(100);
}
