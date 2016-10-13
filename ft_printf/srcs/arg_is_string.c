/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 18:06:55 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/19 20:39:50 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	str_precision(char *str, t_arg *arg, t_env *e)
{
	int i;

	i = 0;
	if (str && !arg->precision_null)
	{
		if (arg->precision && (arg->precision < (int)ft_strlen_ptf(str)))
		{
			while (arg->precision > i)
				ft_putchar_ret(e, str[i++]);
		}
		else
			ft_putstr_ret(e, str);
	}
	else if (!arg->precision_null)
		ft_putstr_ret(e, "(null)");
}

void	print_str(t_env *e, char *str, t_arg *arg)
{
	int		len;
	int		temp;

	temp = 0;
	str ? len = ft_strlen_ptf(str) : 6;
	if (arg->precision_null)
		len = 0;
	if (arg->precision && (len > arg->precision))
		len = arg->precision;
	if (!arg->flags->minus)
	{
		while ((arg->width - temp++) > len)
			(arg->flags->zero) ? ft_putchar_ret(e, '0')
				: ft_putchar_ret(e, ' ');
	}
	str_precision(str, arg, e);
	while (arg->flags->minus && (arg->width > (len + temp++)))
		ft_putchar_ret(e, ' ');
}

void	arg_is_string(t_env *e, t_arg *arg, va_list list)
{
	wchar_t *w_str;
	char	*str;

	if (arg->length->l || arg->specifier == 'S')
	{
		w_str = va_arg(list, wchar_t*);
		print_wstr(e, w_str, arg);
	}
	else
	{
		str = va_arg(list, char*);
		print_str(e, str, arg);
	}
}
