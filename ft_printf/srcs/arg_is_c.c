/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 18:03:42 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/19 18:06:13 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			print_char(t_env *e, t_arg *arg, char c)
{
	int		len;
	int		temp;
	int		i;

	temp = 0;
	i = 0;
	len = 1;
	if (arg->precision)
		len = arg->precision;
	while (arg->precision > (len + temp++) && len > temp)
		ft_putchar_ret(e, '0');
	while (!arg->flags->minus && (arg->width - temp++) >= len)
	{
		if (arg->flags->zero)
			ft_putchar_ret(e, '0');
		else
			ft_putchar_ret(e, ' ');
	}
	ft_putchar_ret(e, c);
	while (arg->flags->minus && (arg->width >= (len + temp++)))
		ft_putchar_ret(e, ' ');
}

void			arg_is_c(t_env *e, t_arg *arg, va_list list)
{
	wchar_t w;

	w = 0;
	if (arg->length->l || arg->specifier == 'C')
	{
		w = va_arg(list, wchar_t);
		arg_is_wchar(e, w);
	}
	else
		print_char(e, arg, va_arg(list, int));
}
