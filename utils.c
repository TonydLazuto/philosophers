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

void	superjoinfree(char *s1, char *s2, char *s3)
{
	char	*str;
	
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2)
			+ ft_strlen(s3) + 2);
	if (!str)
		return ;
	str[0] = '\0';
	str = append_str(str, s1);
	str = append_str(str, " ");
	str = append_str(str, s2);
	str = append_str(str, s3);
	ft_free(&s1);
	ft_free(&s2);
	ft_putstr(str);
	ft_free(&str);
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