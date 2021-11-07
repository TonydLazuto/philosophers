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

t_philo	*launch_threads(t_philo *phil, t_info *info)
{
	pthread_t	th;
	int			i;

	i = 0;
	if (pthread_create(&th, NULL, &observe, (void *)info))
		return (NULL);
	if (pthread_detach(th))
		return (NULL);
	info->start_time = get_time();
	while (i < info->nb_of_philos)
	{
		if (pthread_create(&th, NULL, &routine, (void *)&phil[i]))
			return (NULL);
		if (pthread_detach(th))
			return (NULL);
		i++;
	}
	return (phil);
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
	if (info.nb_of_philos == 1)
	{
//		eat_alone(phil[0]);
		if (!clear_philos(&phil, &info))
			return (-1);
		return (0);
	}
	phil = launch_threads(phil, &info);
	if (!phil)
		return (-1);
	pthread_mutex_lock(&info.end);
	while (info.philos_seated > 0)
		ft_usleep((double)0.1);
	pthread_mutex_unlock(&info.end);
	if (!clear_philos(&phil, &info))
		return (-1);
	return (0);
}
