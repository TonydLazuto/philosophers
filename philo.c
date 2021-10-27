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

void	*check_death(void *arg)
{
	t_philo		*phil;

	phil = (t_philo *)arg;
	ft_usleep(phil->info->time_to_eat + 1);
	while (1)
	{
		if (!phil->last_meal)
			phil->last_meal = phil->start_time;
		if (get_current_time(phil->start_time) - phil->last_meal
				>= phil->info->time_to_die)
		{
			phil->died = 1;
			print_msg(get_current_time(phil->start_time), phil->num, DIED, phil);
			break ;
		}
		if (phil->nb_meals == 0)
			;
//		if (get_current_time(phil->start_time) - phil->last_meal > phil->info->time_to_die / 2)
//			phil->starving = 1;
		ft_usleep(50);
	}
	return (NULL);
}

void	eat_alone(t_philo *phil)
{
	pthread_mutex_lock(phil->right_fork);
	print_msg(get_current_time(phil->start_time), phil->num, TAKEFORK, phil);
	print_msg(get_current_time(phil->start_time), phil->num, EATING, phil);
	while (1)
		ft_usleep(phil->info->time_to_die + 10);
	pthread_mutex_unlock(phil->right_fork);
}

void	*routine(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	int i = 0;
	while (phil->died)
		usleep(50);
	phil->start_time = get_time();
	phil->last_meal = 0;
	if (!phil->right && !phil->left)
		eat_alone(phil);
	while (1)
	{
//		print_msg(get_current_time(phil->start_time), phil->num, " --> get_current_time\n", phil);
//		print_msg(phil->last_meal, phil->num, " ------> last_meal\n", phil);
		wait_for_eat(phil);
		i++;
	}
	return (NULL);
}

int		launch_threads(t_philo *phil)
{
	t_philo		*cpy;

	cpy = phil;
	while (phil)
	{
		if (pthread_create(&phil->pth, NULL, &routine, (void*)phil))
			return (-1);
		if (pthread_create(&phil->death, NULL, &check_death, (void*)phil))
			return (-1);
		phil = phil->right;
	}
	while (cpy)
	{
		if (pthread_detach(cpy->death))
			return (-1);
		if (pthread_join(cpy->pth, NULL))
			return (-1);
		cpy = phil->right;
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
	if (clear_philos(&phil) == -1)
		return (-1);
	return (0);
}
