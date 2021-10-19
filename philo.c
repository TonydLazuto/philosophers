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


void	*eating(t_thread *th, int start_time)
{
	printf("timestamp_in_ms X has taken a fork");
	printf("timestamp_in_ms X is eating");
	while ((get_time() - start_time) - start_time <= th->info->time_to_eat)
		;
	start_time = get_time();
	th = sleeping(th, start_time);
	start_time = get_time();
	th = thinking(th, start_time);
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

void	*routine(void *th)
{
	t_thread	*cpy;
	long		start_time;

	cpy = (t_thread*)th;
	while (1)
	{
		start_time = get_time();
		if (cpy->num % 2)
			try_lock_right();
		else
			tru
		cpy = eating(cpy, start_time);
		start_time = get_time();
		cpy = dying(cpy, start_time);

		ft_usleep(1000);
	}
	if (cpy->info->nb_of_philos >= 2)
	{
//		if (pthread_mutex_lock(&cpy->fork))
//			return (NULL);
		printf("%ldms: %d has taken a fork\n", get_time() - start_time, cpy->num);
	/*	if (pthread_mutex_lock(&cpy->right->fork)) // if (cpy right exist) else (c'est le 1er)
			return (NULL);
		printf("%ldms: %d has taken a fork", get_time() - start_time, cpy->num);
		printf("%ldms: %d is eating", get_time() - start_time, cpy->num);
		usleep(cpy->time_to_eat * 1000);
		if (pthread_mutex_unlock(&cpy->right->fork))
			return (NULL);	
	*/
/*		if (pthread_mutex_unlock(&cpy->fork))
			return (NULL);
		else
			printf("pthread %d cannot lock fork\n", cpy->num);
*/	}
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
	t_thread	*cpy;

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
    }
	if (destroy_mutex(th) == -1)
		return (-1);
	return (0);
}