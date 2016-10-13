/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 18:16:43 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/19 18:23:14 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					print_hex(t_env *e, char spe)
{
	if (spe == 'o' || spe == 'O')
	{
		ft_putchar_ret(e, '0');
		return (1);
	}
	else if (spe == 'x')
		ft_putstr_ret(e, "0x");
	else if (spe == 'X')
		ft_putstr_ret(e, "0X");
	return (2);
}

unsigned long long	get_uns(unsigned long long n, t_length *length, t_arg *arg)
{
	if (arg->specifier == 'O')
		return ((unsigned long long)n);
	else if (arg->specifier == 'U')
		return ((unsigned long)n);
	else if (length->hh)
		return ((unsigned char)n);
	else if (length->h)
		return ((unsigned short int)n);
	else if (length->l)
		return ((unsigned long)n);
	else if (length->no)
		return ((unsigned int)n);
	return (n);
}

void				print_lluint(t_env *e, t_arg *arg, va_list list)
{
	int						len;
	unsigned long long int	n;
	int						temp;
	int						signe;

	signe = 1;
	n = get_uns(va_arg(list, unsigned long long int), arg->length, arg);
	arg->is_unsigned = 1;
	(n == 0) ? (signe *= 0) : (signe *= 1);
	if (n == 0 && arg->precision_null)
		len = 0;
	else
		len = ft_parse_len(n, arg->specifier);
	temp = format_output(e, len, signe, arg);
	if (!format_hex(arg, e, (int)n) && arg->flags->htag)
		ft_putchar_ret(e, '0');
	else if (!n && arg->precision_null)
		;
	else
		parse_number(e, n, arg->specifier);
	while (arg->flags->minus && (arg->width > (len + temp++)))
		ft_putchar_ret(e, ' ');
}

void				arg_is_u(t_env *e, t_arg *arg, va_list list)
{
	print_lluint(e, arg, list);
}
