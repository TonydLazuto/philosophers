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

void	print_msg(long timestamp, int num_philo, char *state, t_philo *phil)
{
	char	*time;
	char	*num_phil;
	char	*msg;

	num_phil = NULL;
	msg = NULL;
	time = ft_itoa(timestamp);
	if (!time)
		return ;
	num_phil = ft_itoa((long)num_philo);
	if (!num_phil)
		return ;
	msg = superjoinfree(time, num_phil, state);
	pthread_mutex_lock(phil->text);
	ft_putstr(msg);
	pthread_mutex_unlock(phil->text);
	ft_free(&msg);
}

void	wait_for_eat(t_philo *phil)
{
	if (phil->num % 2)
	{
		pthread_mutex_lock(phil->left_fork);
//		printf("%ld %d has taken the left fork\n", get_current_time(phil->info->start_time), phil->num);
		print_msg(get_current_time(phil->info->start_time), phil->num, TAKEFORK, phil);
		pthread_mutex_lock(phil->right_fork);
//		printf("%ld %d has taken the right fork\n", get_current_time(phil->info->start_time), phil->num);
		print_msg(get_current_time(phil->info->start_time), phil->num, TAKEFORK, phil);
		eating(phil);
		pthread_mutex_unlock(phil->right_fork);
		pthread_mutex_unlock(phil->left_fork);
	}
	else
	{
		pthread_mutex_lock(phil->right_fork);
//		printf("%ld %d has taken the right fork\n", get_current_time(phil->info->start_time), phil->num);
		print_msg(get_current_time(phil->info->start_time), phil->num, TAKEFORK, phil);
		pthread_mutex_lock(phil->left_fork);
//		printf("%ld %d has taken the left fork\n", get_current_time(phil->info->start_time), phil->num);
		print_msg(get_current_time(phil->info->start_time), phil->num, TAKEFORK, phil);
		eating(phil);
		pthread_mutex_unlock(phil->left_fork);
		pthread_mutex_unlock(phil->right_fork);
	}
}

void	eating(t_philo *phil)
{	
	phil->last_meal = get_time();
	print_msg(get_current_time(phil->info->start_time), phil->num, EATING, phil);
	ft_usleep(phil->info->time_to_eat);
	phil->starving = 0;
	sleeping(phil);
}

void	sleeping(t_philo *phil)
{
	print_msg(get_current_time(phil->info->start_time), phil->num, SLEEPING, phil);
	ft_usleep(phil->info->time_to_sleep);
	thinking(phil);
}

void	thinking(t_philo *phil)
{
	print_msg(get_current_time(phil->info->start_time), phil->num, THINKING, phil);
	ft_usleep(50);
}
