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

void	eat_alone(t_philo *phil)
{
	pthread_t	death;

	phil->info->start_time = get_time();
	phil->last_meal = get_current_time(phil->info->start_time);
	if (pthread_create(&death, NULL, &death_routine, (void *)phil))
		return ;
	if (pthread_detach(death))
		return ;
	pthread_mutex_lock(&phil->right_fork);
	pthread_mutex_lock(&phil->info->status);
	print_msg(phil, TAKEFORK);
	pthread_mutex_unlock(&phil->info->status);
	while (!phil->info->died && phil->nb_meals_eaten
		!= phil->info->nb_meals_to_eat)
		ft_usleep((double)0.5);
	pthread_mutex_unlock(&phil->right_fork);
}

void	wait_for_eat(t_philo *phil)
{
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;

	l_fork = phil->left_fork;
	r_fork = &phil->right_fork;
	if (phil->num % 2 == 0)
	{
		l_fork = &phil->right_fork;
		r_fork = phil->left_fork;
	}
	pthread_mutex_lock(l_fork);
	pthread_mutex_lock(&phil->info->status);
	print_msg(phil, TAKEFORK);
	pthread_mutex_unlock(&phil->info->status);
	pthread_mutex_lock(r_fork);
	pthread_mutex_lock(&phil->info->status);
	print_msg(phil, TAKEFORK);
	pthread_mutex_unlock(&phil->info->status);
}

void	eating(t_philo *phil)
{
	pthread_mutex_lock(&phil->mut);
	phil->last_meal = get_current_time(phil->info->start_time);
	pthread_mutex_lock(&phil->info->status);
	print_msg(phil, EATING);
	pthread_mutex_unlock(&phil->info->status);
	pthread_mutex_lock(&phil->nb_lunch);
	phil->nb_meals_eaten++;
	pthread_mutex_unlock(&phil->nb_lunch);
	pthread_mutex_unlock(&phil->mut);
	ft_usleep(phil->info->time_to_eat);
	pthread_mutex_unlock(&phil->right_fork);
	pthread_mutex_unlock(phil->left_fork);
}

void	sleeping(t_philo *phil)
{
	pthread_mutex_lock(&phil->info->status);
	print_msg(phil, SLEEPING);
	pthread_mutex_unlock(&phil->info->status);
	ft_usleep(phil->info->time_to_sleep);
}

void	thinking(t_philo *phil)
{
	pthread_mutex_lock(&phil->info->status);
	print_msg(phil, THINKING);
	pthread_mutex_unlock(&phil->info->status);
}
