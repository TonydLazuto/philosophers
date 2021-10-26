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



void	eating(t_philo *phil)
{	
//	pthread_mutex_lock(&phil->text);
	printf("%ld %d is eating\n", get_time() - phil->start_time, phil->num);
//	pthread_mutex_unlock(&phil->text);
	ft_usleep(phil->info->time_to_eat);
}


void	sleeping(t_philo *phil)
{
	printf("%ld %d is sleeping\n", get_time() - phil->start_time, phil->num);
	ft_usleep(phil->info->time_to_sleep);
}


void	thinking(t_philo *phil)
{
	printf("%ld %d is thinking\n", get_time() - phil->start_time, phil->num);
	ft_usleep(100);
	printf("%ld %d died\n", get_time()- phil->start_time, phil->num);
//	printf("%d is sleeping\n",phil->num);
}
