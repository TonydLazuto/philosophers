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

int		check_last_meal(t_global *main)
{
	if (main->th->last_meal)
	{
		;
	}
	return (0);
}

void	dying(t_global *main)
{
	long	time;
	long	starving;

	time = 0;
	if (get_time(main->th->start_time) - main->th->start_time
			> main->th->last_meal * 1000)
	{
		;
	}
	while (time < main->info.time_to_die  * 1000)
	{
		if (main->th->has_eaten)
		{
			try_to_eat(main);
		}
		usleep(1000);
		time += 1000;
	}
	printf("%ld %d died\n", get_time(main->th->start_time), main->th->num);
	pthread_detach(main->th->pth);
}

void	sleeping(t_global *main)
{
	printf("%ld %d is sleeping\n", get_time(main->th->start_time), main->th->num);
	usleep(main->info.time_to_sleep * 1000);
	printf("%ld %d is thinking\n", get_time(main->th->start_time), main->th->num);
}

void	eating(t_global *main)
{	
	printf("%ld %d is eating\n", get_time(main->th->start_time), main->th->num);
	usleep(main->info.time_to_eat * 1000);
	main->th->last_meal = get_time(main->th->start_time);
	pthread_mutex_unlock(&main->th->left_fork);
	pthread_mutex_unlock(&main->th->right_fork);
}

void	rest(t_global *main)
{
	if (main->th->has_eaten)
	{
		sleeping(main);
		dying(main);
	}
	else
		dying(main);
}
