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

void	print_msg(t_philo *phil, char *state)
{
	char	*time;
	char	*num_phil;
	int		timestamp;

	num_phil = NULL;
	time = NULL;
	timestamp = get_current_time(phil->info->start_time);
	time = ft_itoa(timestamp);
	if (!time)
		return ;
	num_phil = ft_itoa((long)phil->num);
	if (!num_phil)
		return ;
	if (!phil->info->died)
		concatn_print(time, num_phil, state);	
}

void	wait_for_eat(t_philo *phil)
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

	l_fork = phil->left_fork;
	r_fork = phil->right_fork;
	if (phil->num % 2 == 0)
	{
		l_fork = phil->right_fork;
		r_fork = phil->left_fork;
	}
	pthread_mutex_lock(l_fork);
	pthread_mutex_lock(phil->info->status);
	print_msg(phil, TAKEFORK);
	pthread_mutex_unlock(phil->info->status);
	pthread_mutex_lock(r_fork);
	pthread_mutex_lock(phil->info->status);
	print_msg(phil, TAKEFORK);
	pthread_mutex_unlock(phil->info->status);
}

void	eating(t_philo *phil)
{	
//	print_msg(get_current_time(phil->start_time), phil->num, " --> get_current_time()\n", phil);
//	print_msg(phil->info->time_to_eat, phil->num, " --> time_to_eat\n", phil);
	phil->last_meal = get_current_time(phil->info->start_time);
	pthread_mutex_lock(phil->info->status);
	print_msg(phil, EATING);
	pthread_mutex_unlock(phil->info->status);
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
	usleep(100);
}
