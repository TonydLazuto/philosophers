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

int	launch_detach_threads(t_philo *phil)
{
	pthread_t	death;
	pthread_t	observer;
//	pthread_t	meal;

	if (pthread_create(&observer, NULL, &observe, (void *)phil))
	  	return (-1);
	if (pthread_detach(observer))
	  	return (-1);
	if (pthread_create(&death, NULL, &death_routine, (void *)phil))
	  	return (-1);
	if (pthread_detach(death))
	  	return (-1);
	// if (pthread_create(&meal, NULL, &meal_routine, (void *)phil))
	//   	return (-1);
	// if (pthread_detach(meal))
	//   	return (-1);
	return (0);
}

int	join_threads(t_philo *phil, pthread_t th[])
{
	int	i;

	i = 0;
	while (phil)
	{
		if (pthread_join(th[i], NULL))
			return (-1);
		phil = phil->right;
		i++;
	}
	return (0);
}

int	create_threads(t_philo *phil, t_info *info, pthread_t th[])
{
	int	i;
	
	info->start_time = get_time();
	i = 0;
	while (phil)
	{
		if (pthread_create(&th[i], NULL, &routine, (void *)phil))
			return (-1);
		phil = phil->right;
		i++;
	}
	return (0);
}
int	launch_threads(t_philo *phil, t_info *info)
{
	pthread_t	th[info->nb_of_philos];

	if (create_threads(phil, info, th) == -1)
		return (-1);
	if (join_threads(phil, th) == -1)
		return (-1);
	return (0);
}

int	main(int ac, char *av[])
{
	t_philo		*phil;
	t_info		info;

	phil = NULL;
	if (check_args(ac, av) == -1)
		return (-1);
	phil = init(av, phil, &info);
	if (!phil)
		return (-1);
	if (launch_detach_threads(phil) == -1)
		return (-1);
	if (launch_threads(phil, &info) == -1)
		return (-1);	
	return (0);
}
