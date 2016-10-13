/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_two.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 18:37:17 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/19 19:50:31 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_strcmp_ptf(const char *s1, const char *s2)
{
	int				i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	c1 = s1[i];
	c2 = s2[i];
	if (c1 == c2)
		return (0);
	return (c1 - c2);
}

char	*ft_strncpy_ptf(char *dest, const char *src, size_t n)
{
	char	*ctr;

	ctr = dest;
	while (n > 0 && *src != '\0')
	{
		*ctr++ = *src++;
		--n;
	}
	while (n > 0)
	{
		*ctr++ = '\0';
		--n;
	}
	return (dest);
}

char	*ft_strnew_ptf(size_t size)
{
	size_t	i;
	char	*new;

	i = -1;
	new = (char*)malloc(size + 1);
	if (!new)
		return (NULL);
	while (++i < size + 1)
		new[i] = '\0';
	return (new);
}

size_t	ft_strlen_ptf(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strndup(char *str, int i)
{
	char	*ret;

	if ((ret = (char *)malloc(sizeof(char) * i)) == NULL)
		return (NULL);
	ret = ft_strncpy_ptf(ret, str, i);
	ret[i] = 0;
	return (ret);
}
