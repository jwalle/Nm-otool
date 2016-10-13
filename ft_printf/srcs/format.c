/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 17:47:30 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/19 20:46:33 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		format_hex(t_arg *arg, t_env *e, int signe)
{
	if (arg->flags->htag)
	{
		if (arg->specifier == 'x' || arg->specifier == 'X')
			return (2);
		else if (arg->specifier == 'o' || arg->specifier == 'O')
		{
			if (!signe && arg->precision_null)
			{
				return (0);
			}
			return (1);
		}
	}
	(void)e;
	return (0);
}

int		format_left_width(t_env *e, t_arg *arg, int len, int signe)
{
	int temp;

	temp = 0;
	len += format_hex(arg, e, signe);
	if (arg->precision > len)
		len = arg->precision;
	if (arg->flags->space || (arg->flags->plus && signe >= 0) || signe < 0)
		len++;
	if (!arg->flags->zero && !arg->flags->minus)
	{
		while (((arg->width - temp) > len))
		{
			temp++;
			ft_putchar_ret(e, ' ');
		}
	}
	else if (arg->flags->zero && arg->precision && signe >= 0)
	{
		while (((arg->precision + temp) < arg->width))
		{
			temp++;
			ft_putchar_ret(e, ' ');
		}
	}
	return (temp);
}

int		format_signe(t_env *e, t_arg *arg, int signe)
{
	int		temp;

	temp = 0;
	if (arg->flags->plus && signe >= 0 && !arg->is_unsigned)
	{
		ft_putchar_ret(e, '+');
		temp++;
	}
	else if (signe < 0)
	{
		ft_putchar_ret(e, '-');
		temp++;
	}
	else if (arg->flags->space && !arg->is_unsigned && arg->specifier)
	{
		ft_putchar_ret(e, ' ');
		temp++;
	}
	return (temp);
}

int		format_precision(t_env *e, t_arg *arg, int len, int signe)
{
	int i;

	i = 0;
	if (arg->precision)
	{
		if (signe < 0 && arg->precision > arg->width)
			i--;
		if (arg->flags->minus)
		{
			while (arg->precision > len + i)
			{
				ft_putchar_ret(e, '0');
				i++;
			}
		}
		else if (!arg->flags->minus && arg->precision < arg->width)
		{
			while (arg->precision > len + i)
			{
				ft_putchar_ret(e, '0');
				i++;
			}
		}
	}
	return (i);
}

int		format_output(t_env *e, int len, int signe, t_arg *arg)
{
	int temp;

	temp = format_left_width(e, arg, len, signe) + format_hex(arg, e, signe);
	temp += format_signe(e, arg, signe);
	temp += format_precision(e, arg, len, signe);
	if (signe && arg->hex && arg->flags->htag)
	{
		print_hex(e, arg->specifier);
		if (format_hex(arg, e, signe) == 2 && !arg->flags->zero)
			len -= 2;
	}
	if (!arg->flags->minus)
	{
		while (arg->flags->zero && (arg->width > (len + temp)))
		{
			ft_putchar_ret(e, '0');
			temp++;
		}
		while (arg->precision > (len + temp))
		{
			ft_putchar_ret(e, '0');
			temp++;
		}
	}
	return (temp);
}
