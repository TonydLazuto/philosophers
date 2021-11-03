/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:42:19 by aderose           #+#    #+#             */
/*   Updated: 2021/10/14 18:42:24 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*observe(void *arg)
{
	t_info		*info;

	info = (t_info *)arg;
	while (!info->died && info->philos_seated > 0)
		usleep(100);
	if (info->died)
		return (NULL);
	pthread_mutex_unlock(info->end);
	return (NULL);
}

int	launch_threads(t_philo **myphilos, t_info *info)
{
	pthread_t	th;
	t_philo		*phil;
	
	phil = (t_philo *)*myphilos;
	if (pthread_create(&th, NULL, &observe, (void *)info))
	  	return (-1);
	if (pthread_detach(th))
	  	return (-1);
	info->start_time = get_time();
	while (phil)
	{
		if (pthread_create(&th, NULL, &routine, (void *)phil))
			return (-1);
		if (pthread_detach(th))
			return (-1);
		phil = phil->right;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_philo		*phil;
	t_info		info;

	phil = NULL;
	if (check_args(ac, av) == -1)
		return (-1);
	phil = init(av, phil, &info);
	if (!phil)
		return (-1);
	pthread_mutex_lock(phil->info->end);
	if (launch_threads(&phil, &info) == -1)
		return (-1);
	pthread_mutex_lock(phil->info->end);
	while (phil->info->philos_seated > 0)
		usleep(100);
	pthread_mutex_unlock(phil->info->end);
	return (0);
}
