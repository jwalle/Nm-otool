/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 18:55:50 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/19 19:02:59 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_zero(const char *format, t_arg *arg)
{
	int	i;

	i = 0;
	while (ft_strchr_ptf(FLAGS, format[i]))
	{
		if (format[i] == '-')
			arg->flags->minus = 1;
		if (format[i] == '+')
			arg->flags->plus = 1;
		if (format[i] == '0')
			arg->flags->zero = 1;
		if (format[i] == '#')
			arg->flags->htag = 1;
		if (format[i] == ' ')
			arg->flags->space = 1;
		i++;
	}
	return (i);
}

int		parse_width(const char *format, t_arg *arg, va_list list, int n)
{
	int i;

	i = 0;
	while (ft_isdigit_ptf(format[i + n]) || format[i + n] == '*')
	{
		while (ft_isdigit_ptf(format[i + n]))
			i++;
		if (format[n + i] == '*')
		{
			arg->width = va_arg(list, int);
			n += i + 1;
			i = 0;
		}
	}
	if (i)
		arg->width = ft_atoi_ptf((char *)format + n);
	if (arg->width < 0)
	{
		arg->width *= -1;
		arg->flags->minus = 1;
	}
	return (n + i);
}

int		parse_precision(const char *format, t_arg *arg, va_list list, int n)
{
	int	i;

	i = 0;
	while (ft_isdigit_ptf(format[i + n]) || format[i + n] == '*')
	{
		while (ft_isdigit_ptf(format[i + n]))
			i++;
		if (format[n + i] == '*')
		{
			arg->precision = va_arg(list, int);
			n += i + 1;
			i = 0;
		}
	}
	if (i)
		arg->precision = ft_atoi_ptf((char *)format + n);
	arg->precision == 0 ? arg->precision_null = 1 : 0;
	return (n + i);
}

int		parse(const char *format, t_arg *arg, va_list list)
{
	int		n;

	n = parse_zero(format, arg);
	n = parse_width(format, arg, list, n);
	if (format[n] == '.')
	{
		n = parse_precision(format, arg, list, n + 1);
		if (arg->precision < 0)
		{
			arg->precision = 0;
			return (parse_two(format, arg, n));
		}
	}
	return (parse_two(format, arg, n));
}
