/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_one.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 18:36:48 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/19 19:49:57 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_atoi_ptf(const char *str)
{
	int r;
	int np;

	np = 1;
	r = 0;
	if (!(*str))
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		np = (*str == '-' ? -1 : 1);
		str++;
	}
	while (*str == '0')
		str++;
	while (ft_isdigit_ptf(*str))
	{
		r = r * 10 + (*str - 48);
		str++;
	}
	return (r * np);
}

void	ft_bzero_ptf(void *s, size_t n)
{
	size_t i;

	i = 0;
	while (i != n)
	{
		((char*)s)[i] = '\0';
		i++;
	}
}

int		ft_isdigit_ptf(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

void	ft_putstr_ptf(const char *s)
{
	write(1, s, ft_strlen_ptf(s));
}

char	*ft_strchr_ptf(const char *s, int c)
{
	int i;

	i = ft_strlen_ptf(s);
	while (i >= 0)
	{
		if (s[i] == c)
			return (&((char *)s)[i]);
		i--;
	}
	return (NULL);
}
