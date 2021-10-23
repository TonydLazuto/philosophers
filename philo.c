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

void	try_to_eat(t_philo *phil)
{
//	if (phil->has_eaten)
//		phil->start_time = get_time(phil->start_time);
	if (phil->num % 2)
	{
//		pthread_mutex_lock(&phil->left_fork);
//		printf("%ld %d has taken the left fork\n", get_time(phil->start_time), phil->num);
//		pthread_mutex_lock(&phil->right_fork);
//		printf("%ld %d has taken the other fork\n", get_time(phil->start_time), phil->num);
		eating(phil);
//		pthread_mutex_unlock(&phil->right_fork);
//		pthread_mutex_unlock(&phil->left_fork);
	}
	else
	{
//		pthread_mutex_lock(&phil->right_fork);
//		printf("%ld %d has taken the right fork\n", get_time(phil->start_time), phil->num);
//		pthread_mutex_lock(&phil->left_fork);
//		printf("%ld %d has taken the other fork\n", get_time(phil->start_time), phil->num);
		eating(phil);
//		pthread_mutex_unlock(&phil->left_fork);
//		pthread_mutex_unlock(&phil->right_fork);
	}
}

void	*routine(void *phil)
{
	t_philo *cpy;

	cpy = (t_philo *)phil;
//int	i = 0;
//	cpy->th->start_time = get_time();
//	while (i < 1)
//	{
		eating(cpy);
		sleeping(cpy);
		dying(cpy);
//		i++;
//	}
	return (NULL);
}

int		do_some(t_philo *phil, t_info info)
{
	int			i;
	t_philo		*cpy;

	i = 0;
	cpy = phil;
//	if (!cpy->right)
//		eat_alone();
//	phil = init_forks(phil);
	while (i < info.nb_of_philos)
	{
		if (pthread_create(&phil->pth, NULL, &routine, (void*)phil))
			return (-1);
		usleep(100);
		phil = phil->right;
		i++;
	}
	i = 0;
	while (i < info.nb_of_philos)
	{
		if (pthread_join(cpy->pth, NULL))
			return (-1);
		cpy = cpy->right;
		i++;
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
	if (do_some(phil, info) == -1)
		return (-1);
//	if (destroy_mutex(&phil) == -1)
//		return (-1);
	clear_philos(&phil);
	return (0);
}
