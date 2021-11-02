/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:32:21 by aderose           #+#    #+#             */
/*   Updated: 2021/10/18 11:32:23 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(char **s)
{
	free(*s);
	*s = NULL;
}

char	*append_str(char *str, char *s)
{
	int		i;
	int		len;

	len = ft_strlen(str);
	i = 0;
	while (s[i])
	{
		str[len + i] = s[i];
		i++;
	}
	str[len + i] = '\0';
	return (str);
}

void	concatn_print(char *time, char *num_phil, char *state)
{
	char	*statut;
	
	statut = (char *)malloc(ft_strlen(time) + ft_strlen(num_phil)
			+ ft_strlen(state) + 2);
	if (!statut)
		return ;
	statut[0] = '\0';
	statut = append_str(statut, time);
	statut = append_str(statut, " ");
	statut = append_str(statut, num_phil);
	statut = append_str(statut, state);
	ft_free(&time);
	ft_free(&num_phil);
	ft_putstr(statut);
	ft_free(&statut);
}

long	set_size(long nb)
{
	long	size;

	size = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(long nb)
{
	char	*s;
	long	size;

	size = set_size(nb);
	s = (char *)malloc(size + 1);
	if (!s)
		return (NULL);
	if (nb == 0)
		s[0] = '0';
	s[size] = '\0';
	while (nb > 0)
	{
		size--;
		s[size] = nb % 10 + '0';
		nb /= 10;
	}
	return (s);
}