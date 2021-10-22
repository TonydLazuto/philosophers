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


void	dying(t_thread *th, int start_time)
{
	th->has_eaten = 0;
	usleep(th->info.time_to_die);
	printf("%ldms: %d died\n", get_time() - start_time, th->num);
	pthread_detach(th->pth);
}

void	sleeping(t_thread *th, int start_time)
{
	printf("%ldms: %d is sleeping\n", get_time() - start_time, th->num);
	usleep(th->info.time_to_sleep);
	printf("%ldms: %d is thinking\n", get_time() - start_time, th->num);
	dying(th, start_time);
}

int		lock_l_fork(t_thread *th, int start_time, pthread_mutex_t l_fork)
{
	if (pthread_mutex_lock(&l_fork))
		return (-1);
	printf("%ldms: %d has taken a l_fork\n", get_time() - start_time, th->num);
	printf("%ldms: %d is eating\n", get_time() - start_time, th->num);
	th->last_meal = get_time() - start_time;
	usleep(th->info.time_to_eat);
	th->has_eaten = 1;
	pthread_mutex_unlock(&l_fork);
	pthread_mutex_unlock(&th->r_fork);
	return (0);
}

int		lock_r_fork(t_thread *th, int start_time)
{
//	printf("%ldms: %d try to take a r_fork\n", get_time() - start_time, th->num);
	if (pthread_mutex_lock(&th->r_fork))
		return (-1);
	printf("%ldms: %d has taken a r_fork\n", get_time() - start_time, th->num);
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
	while (1) {
	cpy->has_eaten = 0; // useless ?
	if (lock_r_fork(cpy, start_time) == 0)
	{
		if (cpy->has_eaten == 1)
			sleeping(cpy, start_time);
		else
			dying(cpy, start_time);
	}
	else
		dying(cpy, start_time);
	}
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
	long start = get_time();

	th = NULL;
	if (check_args(ac, av, &info) == -1)
		return (-1);
	th = init(th, info);
	if (!th)
		return (-1);
	while (1)
    {
		//if (do_some(th) == -1)
		//	return (-1);
		printf("%ld\n", get_time() - start);
		ft_usleep(410);
    }
	if (destroy_mutex(th) == -1)
		return (-1);
	return (0);
}