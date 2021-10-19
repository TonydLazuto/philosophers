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

/*
	wait(chopstick[i])
	wait(chopstick[(i+1) % 5])
*/

void	*routine(void *th)
{
	t_thread	*cpy;
	long		start_time;

	start_time = get_time();
	cpy = (t_thread*)th;
	if (cpy->info->nb_of_philos >= 2)
	{
		if (pthread_mutex_lock(&cpy->fork))
			return (NULL);
		printf("%ldms: %ld has taken a fork", get_time() - start_time, cpy->pth);
	/*	if (pthread_mutex_lock(&cpy->right->fork)) // if (cpy right exist) else (c'est le 1er)
			return (NULL);
		printf("%ldms: %d has taken a fork", get_time() - start_time, cpy->pth);
		printf("%ldms: %d is eating", get_time() - start_time, cpy->pth);
		usleep(cpy->time_to_eat * 1000);
		if (pthread_mutex_unlock(&cpy->right->fork))
			return (NULL);	
	*/
		if (pthread_mutex_unlock(&cpy->fork))
			return (NULL);
		else
			printf("pthread %ld cannot lock fork\n", cpy->pth);
	}
/*
	if (get_time() - start_time >= cpy->time_to_die)
		pthread_detach(cpy->id[cpy->num]);
	if (cpy->nb_of_philos == 1)
		;//dying
*/	
	return ((void*)cpy);
}

int		do_some(t_thread *th)
{
	t_thread *cpy;

	cpy = th;
	while (cpy)
	{
		if (pthread_create(&cpy->pth, NULL, &routine, (void*)cpy))
			return (-1);
		cpy = cpy->right;
	}
	cpy = th;
	while (cpy)
	{
		if (pthread_join(cpy->pth, (void**)cpy))
			return (-1);
		cpy = cpy->right;
	}
	return (0);
}

int main(int ac, char *av[])
{
	t_thread	*th;
	t_info		info;

	th = NULL;
	if (check_args(ac, av, &info) == -1)
		return (-1);
	if (init(&th, info) == -1)
		return (-1);
	while (1)
    {
		if (do_some(th) == -1)
			return (-1);
		ft_usleep(100);
    }
	if (destroy_mutex(th) == -1)
		return (-1);
	return (0);
}