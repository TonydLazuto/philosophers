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

int		check_death(t_philo *phil, pthread_mutex_t *r_fork,
			pthread_mutex_t * l_fork)
{
	ft_usleep(0.05);
	if (phil->info->someone_died)
	{
		if (r_fork)
			pthread_mutex_unlock(phil->right_fork);
		if (l_fork)
			pthread_mutex_unlock(phil->left_fork);
		return (1);
	}
	return (0);
}

void	wait_for_eat(t_philo *phil)
{
	if (phil->num % 2)
	{
		pthread_mutex_lock(phil->left_fork);
		if (check_death(phil, NULL, phil->left_fork))
			return ;
		print_msg(get_current_time(phil->start_time), phil->num, TAKEFORK, phil);
		pthread_mutex_lock(phil->right_fork);
		if (check_death(phil, phil->right_fork, phil->left_fork))
			return ;
		print_msg(get_current_time(phil->start_time), phil->num, TAKEFORK, phil);
		eating(phil);
	}
	else
	{
		pthread_mutex_lock(phil->right_fork);
		if (check_death(phil, phil->right_fork, NULL))
			return ;
		print_msg(get_current_time(phil->start_time), phil->num, TAKEFORK, phil);
		pthread_mutex_lock(phil->left_fork);
		if (check_death(phil, phil->right_fork, phil->left_fork))
			return ;
		print_msg(get_current_time(phil->start_time), phil->num, TAKEFORK, phil);
		eating(phil);
	}
}

void	eating(t_philo *phil)
{	
//	print_msg(get_current_time(phil->start_time), phil->num, " --> get_current_time()\n", phil);
//	print_msg(phil->info->time_to_eat, phil->num, " --> time_to_eat\n", phil);
	ft_usleep(0.05);
	phil->last_meal = get_current_time(phil->start_time);
	print_msg(get_current_time(phil->start_time), phil->num, EATING, phil);

	while (get_current_time(phil->start_time) - phil->last_meal < phil->info->time_to_eat)
	{
		if (check_death(phil, phil->right_fork, phil->left_fork))
			return ;
	}
	pthread_mutex_unlock(phil->right_fork);
	pthread_mutex_unlock(phil->left_fork);
//	phil->nb_meals--;
//	phil->starving = 0;
}

void	sleeping(t_philo *phil)
{
	print_msg(get_current_time(phil->start_time), phil->num, SLEEPING, phil);
	while (get_current_time(phil->start_time) - phil->last_meal
		+ phil->info->time_to_eat < phil->info->time_to_sleep)
	{
		if (check_death(phil, NULL, NULL))
			return ;
		ft_usleep(0.05);
	}
}

void	thinking(t_philo *phil)
{
	print_msg(get_current_time(phil->start_time), phil->num, THINKING, phil);
	ft_usleep(0.05);
}
