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

void	eat_alone(t_philo *phil)
{
	pthread_mutex_lock(phil->right_fork);
	print_msg(get_current_time(phil->start_time), phil->num, TAKEFORK, phil);
	pthread_mutex_unlock(phil->right_fork);
}

int		launch_threads(t_philo *phil)
{
	t_philo		*cpy;

	cpy = phil;
	while (phil)
	{
		if (pthread_create(&phil->pth, NULL, &routine, (void*)phil))
			return (-1);
		phil = phil->right;
	}
	while (cpy)
	{
		if (pthread_join(cpy->pth, NULL))
			return (-1);
		cpy = cpy->right;
	}
	return (0);
}

int		main(int ac, char *av[])
{
	t_philo		*phil;
	t_info		info;

	phil = NULL;
	if (check_args(ac, av) == -1)
		return (-1);
	phil = init(av, phil, &info);
	if (!phil)
		return (-1);
	if (launch_threads(phil) == -1)
		return (-1);
//	if (clear_philos(&phil) == -1)
//		return (-1);
	return (0);
}
