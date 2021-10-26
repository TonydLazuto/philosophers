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

void	print_msg(long timestamp, int num_philo, char *state)
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
	ft_putstr(msg);
	ft_free(&msg);
}

void	eating(t_philo *phil)
{	
	phil->last_meal = get_time() - phil->info->start_time;
	pthread_mutex_lock(phil->text);
	print_msg(get_current_time(phil->info->start_time), phil->num, EATING);
//	printf("%ld %d is eating\n", get_current_time(phil->info->start_time), phil->num);
	ft_usleep(phil->info->time_to_eat);
	pthread_mutex_unlock(phil->text);
	sleeping(phil);
}

void	sleeping(t_philo *phil)
{
	pthread_mutex_lock(phil->text);
	print_msg(get_current_time(phil->info->start_time), phil->num, SLEEPING);
//	printf("%ld %d is sleeping\n", get_current_time(phil->info->start_time), phil->num);
	ft_usleep(phil->info->time_to_sleep);
	pthread_mutex_unlock(phil->text);
	thinking(phil);
}

void	thinking(t_philo *phil)
{
	pthread_mutex_lock(phil->text);
	print_msg(get_current_time(phil->info->start_time), phil->num, THINKING);
	//printf("%ld %d is thinking\n", get_current_time(phil->info->start_time), phil->num);
	while (1) // TRY_TO_EAT
	{
		if (get_current_time(phil->info->start_time) - phil->last_meal > phil->info->time_to_die)
			break ;
		//printf("time since last meal : %ld %d\n", get_current_time(phil->info->start_time)-phil->last_meal, phil->num);
		ft_usleep(50);
	}
	pthread_mutex_unlock(phil->text);
	pthread_mutex_lock(phil->text);
	print_msg(get_current_time(phil->info->start_time), phil->num, DIED);
//	printf("%ld %d died\n", get_time()- phil->info->start_time, phil->num);
	pthread_mutex_unlock(phil->text);
}
