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

void	sleeping(t_thread *th, int start_time)
{
	start_time = get_time();
	printf("%ldms %d is sleeping", get_time() - start_time, th->num);
	ft_usleep(th->info->time_to_sleep * 1000);
}

void	thinking(t_thread *th, int start_time)
{
	start_time = get_time();
	printf("%ldms %d is thinking", get_time() - start_time, th->num);
}

void	dying(t_thread *th, int start_time)
{
	th->has_eaten = 0;
	start_time = get_time();
	ft_usleep(th->info->time_to_die * 1000);
	printf("%ldms %d died", get_time() - start_time, th->num);
	pthread_detach(th);
}

int		lock_l_fork(t_thread *th, int start_time, pthread_mutex_t l_fork)
{
	if (pthread_mutex_lock(&l_fork))
		return (-1);
	printf("%ldms %d has taken a l_fork", get_time() - start_time, th->num);
	printf("%ldms %d is eating", get_time() - start_time, th->num);
	th->last_meal = get_time() - start_time;
	ft_usleep(th->info->time_to_eat * 1000);
	th->has_eaten = 1;
	if (pthread_mutex_unlock(&l_fork))
		pthread_mutex_unlock(&th->r_fork);
	return (0);
}

int		lock_r_fork(t_thread *th, int start_time)
{
	if (pthread_mutex_lock(&th->r_fork))
		return (-1);
	printf("%ldms: %d has taken a r_fork", get_time() - start_time, th->num);
	if (th->left)
	{
		if (lock_l_fork(th, start_time, th->left->r_fork) == -1)
			pthread_mutex_unlock(&th->r_fork);
	}
	else
	{
		if (lock_l_fork(th, start_time, last_thread(th)->r_fork) == -1)
			pthread_mutex_unlock(&th->r_fork);
	}
	return (0);
}

void	*routine(void *th)
{
	t_thread	*cpy;
	long		start_time;

	cpy = (t_thread*)th;
	start_time = get_time();
	cpy->has_eaten = 0; // useless ?
	if (lock_r_fork(cpy, start_time) != -1)
	{
		if (cpy->has_eaten == 1)
		{
			sleeping(cpy, start_time);
			thinking(cpy, start_time);
		}
		else
			dying(cpy, start_time);
	}
	else
		dying(cpy, start_time);
	return (NULL);
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
		if (pthread_join(cpy->pth, NULL))
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