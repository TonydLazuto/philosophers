/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:17:14 by aderose           #+#    #+#             */
/*   Updated: 2021/10/18 11:17:15 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eating(void *pth)
{
	printf("timestamp_in_ms X has taken a fork");
	printf("timestamp_in_ms X is eating");
}

void	*sleeping(void *pth)
{
	printf("timestamp_in_ms X is sleeping");
}

void	*thinking(void *pth)
{
	printf("timestamp_in_ms X is thinking");
}

void	dying(void *pth)
{
	printf("timestamp_in_ms X is died");
}