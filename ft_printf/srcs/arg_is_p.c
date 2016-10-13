/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 18:23:38 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/19 18:36:58 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		sub_hex(t_env *e, t_arg *arg, int len, int temp)
{
	if (!arg->flags->minus)
	{
		while (!arg->flags->zero && ((arg->width - temp++) > len))
			ft_putchar_ret(e, ' ');
		ft_putstr_ret(e, "0x");
		while (arg->flags->zero && ((arg->width - temp++) > len))
			ft_putchar_ret(e, '0');
	}
	else
		ft_putstr_ret(e, "0x");
	return (temp);
}

void	print_ptr(t_env *e, t_arg *arg, va_list list)
{
	int		len;
	int		temp;
	void	*ptr;

	temp = 2;
	len = 1;
	ptr = va_arg(list, void*);
	if (ptr)
		len = ft_int_hex_len((unsigned long long)ptr);
	temp = sub_hex(e, arg, len, temp);
	while (arg->precision + 3 > (len + temp++))
		ft_putchar_ret(e, '0');
	if (!ptr && arg->precision_null)
		;
	else
		ft_putnbr_hexa(e, (unsigned long long)ptr, 'x');
	while (arg->flags->minus && (arg->width >= (len + temp++)))
		ft_putchar_ret(e, ' ');
}

void	arg_is_p(t_env *e, t_arg *arg, va_list list)
{
	print_ptr(e, arg, list);
}
