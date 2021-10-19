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

void	*try_to_eat(t_thread *th, int start_time)
{
	printf("timestamp_in_ms X has taken a fork");
	printf("timestamp_in_ms X is eating");
	while ((get_time() - start_time) - start_time <= th->info->time_to_eat)
		;
	th->last_meal = get_time() - start_time;
}

void	*sleeping(t_thread *th, int start_time)
{
	printf("timestamp_in_ms X is sleeping");
	while ((get_time() - start_time) - start_time <= th->info->time_to_sleep)
		;
}

void	*thinking(t_thread *th, int start_time)
{
	printf("timestamp_in_ms X is thinking");
}

void	*dying(t_thread *th, int start_time)
{
	printf("timestamp_in_ms X died");
	while ((get_time() - start_time) - start_time <= th->info->time_to_die)
		;
}