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
	print_msg(get_current_time(phil->start_time), phil->num, TAKEFORK);
	pthread_mutex_unlock(phil->right_fork);
}

void    *observe(void *arg)
{
	t_philo		*phil;
	t_philo		*start;

	phil = (t_philo *)arg;
	start = phil;
	while (phil)
	{
		usleep(100);
		if (phil->died)
		{
			break ;
			printf("Merde ils ont tues kenny espece d'en****\n");
		}
		phil = phil->right;
		if (!phil)
			phil = start;
	}
	
//	if (clear_philos(&phil) == -1)
//		return (NULL);
	return (NULL);
}

int		launch_observer(t_philo *phil)
{
	pthread_t watch;

	if (pthread_create(&watch, NULL, &observe, (void*)phil))
		return (-1);
	if (pthread_detach(watch))
		return (-1);
	return (0);
}

int		launch_threads(t_philo *phil)//, t_info *info)
{
	t_philo		*cpy;
	pthread_t	th;

	cpy = phil;
	if (launch_observer(phil) == -1)
		return (-1);
	while (phil)
	{
		if (pthread_create(&th, NULL, &routine, (void*)phil))
			return (-1);
		phil = phil->right;
	}
	while (cpy)
	{
		if (pthread_join(th, NULL))
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
