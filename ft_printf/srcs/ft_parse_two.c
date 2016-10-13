/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 10:32:34 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/24 10:32:36 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_length(t_arg *arg, char *len_parse)
{
	if (!len_parse)
	{
		arg->length->no = 1;
		return ;
	}
	arg->length->no = 0;
	if (!ft_strcmp_ptf(len_parse, "hh"))
		arg->length->hh = 1;
	else if (!ft_strcmp_ptf(len_parse, "h"))
		arg->length->h = 1;
	else if (!ft_strcmp_ptf(len_parse, "l"))
		arg->length->l = 1;
	else if (!ft_strcmp_ptf(len_parse, "ll"))
		arg->length->ll = 1;
	else if (!ft_strcmp_ptf(len_parse, "j"))
		arg->length->j = 1;
	else if (!ft_strcmp_ptf(len_parse, "z"))
		arg->length->z = 1;
}

int		is_hex(char spe)
{
	if (spe == 'o' || spe == 'O')
		return (1);
	else if (spe == 'x' || spe == 'X')
		return (2);
	return (0);
}

int		parse_two(const char *format, t_arg *arg, int n)
{
	int		i;
	char	*len_parse;

	i = 0;
	init_length(arg->length);
	if (ft_strchr_ptf(LENGTH, format[i + n]))
	{
		while (ft_strchr_ptf(LENGTH, format[i + n]))
			i++;
		len_parse = ft_strndup((char *)format + n, i);
		n += i;
		parse_length(arg, len_parse);
		free(len_parse);
	}
	arg->specifier = format[n++];
	arg->hex = is_hex(arg->specifier);
	return (n);
}
