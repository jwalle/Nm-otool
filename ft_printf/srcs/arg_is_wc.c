/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is_wc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 20:17:19 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/19 20:17:31 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_putwchar(t_env *e, unsigned char *str, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		write(1, &str[i], 1);
		e->ret++;
		i++;
	}
}

int				get_wchar_len(wchar_t c)
{
	if (c <= 0x7F)
		return (1);
	else if (c >= 0xD800 && c < 0xF900)
		return (-1);
	else if (c <= 0x07FF)
		return (2);
	else if (c <= 0xFFFF)
		return (3);
	else if (c <= 0x10FFFF)
		return (4);
	else
		return (-1);
}

unsigned char	*convert_wchar(unsigned char *str, wchar_t c, int len)
{
	if (len == 1)
		str[0] = (char)c;
	else if (len == 2)
	{
		str[0] = ((c >> 6) | 0xC0);
		str[1] = ((c & 0x3F) | 0x80);
	}
	else if (len == 3)
	{
		str[0] = ((c >> 12) | 0xE0);
		str[1] = (((c >> 6) & 0x3F) | 0x80);
		str[2] = ((c & 0x3F) | 0x80);
	}
	else if (len == 4)
	{
		str[0] = ((c >> 18) | 0xF0);
		str[1] = (((c >> 12) & 0x3F) | 0x80);
		str[2] = (((c >> 6) & 0x3F) | 0x80);
		str[3] = ((c & 0x3F) | 0x80);
	}
	str[4] = 0;
	return (str);
}

void			arg_is_wchar(t_env *e, wchar_t w)
{
	unsigned char	str[5];
	int				len;

	ft_bzero_ptf(str, 5);
	len = get_wchar_len(w);
	if (len < 0)
	{
		e->ret = -1;
		return ;
	}
	convert_wchar(str, w, len);
	ft_putwchar(e, str, len);
}
