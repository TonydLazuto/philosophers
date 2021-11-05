/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:13:19 by aderose           #+#    #+#             */
/*   Updated: 2021/10/26 14:13:21 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlcpy(char *dst,
			const char *src, int dstsize)
{
	int	i;

	i = 0;
	if (src == 0)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] && i < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	if (dstsize <= ft_strlen(src))
		return (ft_strlen(src));
	return (i);
}

char	*ft_strcat(char *dst, const char *src)
{
	int		j;
	int		len;
	char	*str;

	len = ft_strlen(dst);
	j = 0;
	while (src[j])
	{
		dst[len + j] = src[j];
		j++;
	}
	dst[len + j] = '\0';
	str = &dst[0];
	return (str);
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

char	*ft_itoa(long nb, char *s)
{
	long	size;

	size = set_size(nb);
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

void	print_msg(t_philo *phil, char *state)
{
	char	buf[40];
	char	tmp[20];
	char	*ret;

	ret = ft_itoa(get_current_time(phil->info->start_time), tmp);
	ft_strlcpy(buf, ret, ft_strlen(ret));
	ft_strcat(buf, " ");
	ret = ft_itoa((long)phil->num, tmp);
	ft_strcat(buf, ret);
	ft_strcat(buf, state);
	if (!phil->info->died)
		ft_putstr(buf);
	ret = NULL;
}
