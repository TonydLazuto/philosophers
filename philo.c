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

//wait(chopstick[i])
//wait(chopstick[(i+1) % 5])

long    get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	*eating(void *pth)
{
	pthread_t *my_pth;

	my_pth = (pthread_t*)pth;
	printf("timestamp_in_ms X has taken a fork");
	printf("timestamp_in_ms X is eating");
}

int		philos_init(t_thread *pth, t_arg arg)
{
	int	i;

	i = 0;
	while (i < arg.nb_of_philos)
	{
		pth->num_thread = i;
		if (pthread_create(&pth->th_id[i], NULL, &eating, (void*)pth) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < arg.nb_of_philos)
	{
		if (pthread_join(pth->th_id[i], (void**)pth))
			return (-1);
		i++;
	}
}

int main(int ac, char *av[])
{
	t_arg		arg;
	t_thread	pth;
	long		start_time;
		
	// Remember when we started
	start_time = get_time();
	if (check_args(ac, av, &arg) == -1)
		return (-1);
	pth.th_id = (pthread_t*)malloc(sizeof(pthread_t) * arg.nb_of_philos);
	if (!pth.th_id)
		return (-1);
	if (philos_init(&pth, arg) == -1)
		return (-1);
	while (1)
    {
		// Print time from start, in ms
        printf("%ld\n", get_time() - start_time);
		// Sleep 200 times 1000 microseconds (1 millisecond)
        usleep(200 * 1000);
    }
	return (0);
}