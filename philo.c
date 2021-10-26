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

	if a philosopher doesn’t start eating ’time_to_die’
	milliseconds after starting his last meal
	or the beginning of the simulation, it dies
*/

void	*check_death(void *phil)
{
	t_philo		*cpy;

	cpy = (t_philo *)phil;
	ft_usleep(cpy->info->time_to_eat + 1);
	while (1)
	{
		if (!cpy->last_meal)
			cpy->last_meal = cpy->info->start_time;
		if (get_current_time(cpy->info->start_time) - cpy->last_meal
				>= cpy->info->time_to_die)
		{
			cpy->died = 1;
//			pthread_mutex_lock(cpy->text);
			print_msg(get_current_time(cpy->info->start_time), cpy->num, DIED, cpy);
		//	printf("%ld %d died\n", get_time()- cpy->info->start_time, cpy->num);
//			pthread_mutex_unlock(cpy->text);
			break ;
		}
//		if (get_current_time(cpy->info->start_time) - cpy->last_meal > cpy->info->time_to_die / 2)
//			cpy->starving = 1;
		ft_usleep(50);
	}
	return (NULL);
}

void	*routine(void *phil)
{
	t_philo	*cpy;

	cpy = (t_philo *)phil;
	int i = 0;
//	try_to_eat(cpy);
//	if (pthread_create(&cpy->death, NULL, &check_death, (void*)cpy))
//		return (NULL);
	while (i < 5)
	{
		try_to_eat(cpy);
		i++;
	}
//	if (pthread_detach(cpy->death))
//		return (NULL);
	return (NULL);
}

int		do_some(t_philo *phil, t_info *info)
{
	t_philo		*cpy;

	cpy = phil;
//	if (!cpy->right)
//		eat_alone();
	info->start_time = get_time();
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
	if (do_some(phil, &info) == -1)
		return (-1);
	if (clear_philos(&phil) == -1)
		return (-1);
	return (0);
}
