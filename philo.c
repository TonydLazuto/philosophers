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

int		try_lock_other_fork(t_global *main, pthread_mutex_t *other_fork)
{
	if (pthread_mutex_lock(other_fork) == 0)
	{
		printf("%ld %d has taken the other fork\n", get_time(main->th->start_time), main->th->num);
		eating(main);
		return (1);
	}
	return (0);
}

void	try_to_eat(t_global *main)
{
	if (main->th->has_eaten)
		main->th->start_time = get_time(main->th->start_time);
	if (main->th->num % 2)
	{
		if (pthread_mutex_lock(&main->th->left_fork) == 0)
		{
			printf("%ld %d has taken the left fork\n", get_time(main->th->start_time), main->th->num);
			if (!try_lock_other_fork(main, &main->th->right_fork))
				pthread_mutex_unlock(&main->th->left_fork);
		}
	}
	else
	{
		if (pthread_mutex_lock(&main->th->right_fork) == 0)
		{
			printf("%ld %d has taken the right fork\n", get_time(main->th->start_time), main->th->num);
			if (!try_lock_other_fork(main, &main->th->left_fork))
				pthread_mutex_unlock(&main->th->right_fork);
		}
	}
}

void	*routine(void *main)
{
	t_global	*cpy;

	cpy = (t_global*)main;
	while (1)
	{
		cpy->th->start_time = get_time(cpy->th->start_time);
		cpy->th->has_eaten = 0;
		try_to_eat(cpy);
		rest(cpy);
	}
	return (NULL);
}

int		do_some(t_global main)
{
	t_thread	*cpy;

	cpy = main.th;
//	if (!cpy->right)
//		eat_alone();
	main.th = init_forks(main.th);
	while (main.th)
	{
		if (pthread_create(&main.th->pth, NULL, &routine, (void*)&main))
			return (-1);
		main.th = main.th->right;
	}
	main.th = cpy;
	while (main.th)
	{
		if (pthread_join(main.th->pth, NULL))
			return (-1);
		main.th = main.th->right;
	}
	return (0);
}

int main(int ac, char *av[])
{
	t_global	main;

	main.th = NULL;
	main.buf = NULL;
	if (check_args(ac, av) == -1)
		return (-1);
	if (init(av, &main) == -1)
		return (-1);
	if (do_some(main) == -1)
		return (-1);
	if (destroy_mutex(&main) == -1)
		return (-1);
	return (0);
}
