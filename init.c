/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 08:30:17 by aderose           #+#    #+#             */
/*   Updated: 2021/10/22 08:30:18 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			init(char *av[], t_global *main)
{
	t_thread	*last;
	int			i;

	i = 0;
	main->info.nb_of_philos = ft_atoi(av[1]);
	main->info.time_to_die = ft_atoi(av[2]);
	main->info.time_to_eat = ft_atoi(av[3]);
	main->info.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		main->info.nb_meals = ft_atoi(av[5]);
	else
		main->info.nb_meals = 0;
	while (i < main->info.nb_of_philos)
	{
		main->th = push_back(main->th, i + 1);
		if (!main->th)
			return (-1);
		last = last_thread(main->th);
		pthread_mutex_init(&last->right_fork, NULL);
		pthread_mutex_init(&last->left_fork, NULL);
		i++;
	}
	return (0);
}

int			destroy_mutex(t_global *main)
{
	int i;

	i = 0;
	while (i < main->info.nb_of_philos)
	{
		if (pthread_mutex_destroy(&main->th->right_fork))
			return (-1);
		if (pthread_mutex_destroy(&main->th->left_fork))
			return (-1);
		i++;
	}
	return (0);
}

t_thread	*init_forks(t_thread *th)
{
	t_thread	*cpy;

	cpy = th;
	while (cpy)
	{
		if (cpy->right)
			cpy->right_fork = cpy->right->left_fork;
		else
			cpy->right_fork = th->left_fork;
		if (cpy->left)
			cpy->left_fork = cpy->left->right_fork;
		else
			cpy->left_fork = last_thread(th)->right_fork;
		cpy = cpy->right;
	}
	return (th);
}