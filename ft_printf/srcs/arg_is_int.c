/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 18:15:15 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/19 18:21:47 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	check_signed(long long n, t_length *length, t_arg *arg)
{
	if (length->hh)
	{
		if (arg->specifier == 'D')
			return ((unsigned short)n);
		else
			return ((signed char)n);
	}
	else if (length->h)
	{
		if (arg->specifier == 'D')
			return ((unsigned short)n);
		else
			return ((short int)n);
	}
	else if (length->l || arg->specifier == 'D')
		return ((long)n);
	else if (length->no)
		return ((int)n);
	else if (length->j)
		return ((intmax_t)n);
	else if (length->z)
		return ((size_t)n);
	return (n);
}

void		print_llint(t_env *e, t_arg *arg, va_list list)
{
	int					len;
	int					signe;
	long long int		n;
	int					temp;

	signe = 1;
	n = check_signed(va_arg(list, long long int), arg->length, arg);
	(n < 0) ? (signe *= -1) : (signe *= 1);
	if (n == 0)
		signe = 0;
	(n < 0) ? (n *= -1) : (n *= 1);
	if (n == 0 && arg->precision_null)
		len = 0;
	else
		len = ft_parse_len(n, arg->specifier);
	temp = format_output(e, len, signe, arg);
	if (!n && arg->precision_null)
		;
	else
		parse_number(e, n, arg->specifier);
	while (arg->flags->minus && (arg->width > (len + temp++)))
		ft_putchar_ret(e, ' ');
}

void		arg_is_int(t_env *e, t_arg *arg, va_list list)
{
	print_llint(e, arg, list);
}
