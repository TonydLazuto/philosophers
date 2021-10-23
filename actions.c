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

void	dying(t_philo *phil)
{
//	phil->start_time = get_time(phil->start_time);
//	printf("%ld %d is thinking\n", get_time() - phil->start_time, phil->num);
	printf("%d is thinking\n",phil->num);
//	usleep(phil->info.time_to_sleep * 1000);
//	printf("%ld %d died\n", get_time(), phil->num);
}

void	sleeping(t_philo *phil)
{
//	phil->start_time = get_time(phil->start_time);
//	printf("%ld %d is sleeping\n", get_time() - phil->start_time, phil->num);
	printf("%d is sleeping\n",phil->num);
//	usleep(phil->info.time_to_sleep * 1000);
}

void	eating(t_philo *phil)
{	
//	phil->start_time = get_time(phil->start_time);
//	printf("%ld %d is eating\n", get_time() - phil->start_time, phil->num);
	printf("%d is eating\n",phil->num);
//	usleep(phil->info.time_to_eat * 1000);
}
