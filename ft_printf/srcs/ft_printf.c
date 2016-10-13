/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 19:30:02 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/30 17:02:45 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_specifier(t_env *e, t_arg *arg, va_list list)
{
	char specifier;

	specifier = arg->specifier;
	if (specifier == 'd' || specifier == 'i' || specifier == 'D')
		arg_is_int(e, arg, list);
	else if (specifier == 'u' || specifier == 'U' || specifier == 'o'
		|| specifier == 'O' || specifier == 'x' || specifier == 'X')
		arg_is_u(e, arg, list);
	else if (specifier == 'c' || specifier == 'C')
		arg_is_c(e, arg, list);
	else if (specifier == 's' || specifier == 'S')
		arg_is_string(e, arg, list);
	else if (specifier == 'p')
		arg_is_p(e, arg, list);
	else if (specifier == '%')
		print_char(e, arg, '%');
	else
		print_char(e, arg, specifier);
}

void	parse_number(t_env *e, long long number, char spe)
{
	if (spe == 'o' || spe == 'O')
	{
		ft_putnbr_octal(e, number);
		return ;
	}
	else if (spe == 'x' || spe == 'X')
	{
		ft_putnbr_hexa(e, number, spe);
		return ;
	}
	ft_putllunbr(e, number);
}

int		process_format(const char *format, t_arg *arg, va_list list, t_env *e)
{
	int i;

	i = 0;
	while (format[i])
	{
		if (format[i] == '{')
			i += process_color(e, &format[i + 1]);
		if (format[i] == '%')
		{
			if (!format[i + 1])
				return (0);
			init_arg(arg);
			i += 1 + parse(&format[i] + 1, arg, list);
			parse_specifier(e, arg, list);
		}
		else
			ft_putchar_ret(e, format[i++]);
	}
	return (1);
}

int		ft_printf(const char *format, ...)
{
	va_list	list;
	t_arg	*arg;
	t_env	*e;
	int		ret;

	if (!format)
		return (-1);
	arg = (t_arg*)malloc(sizeof(t_arg));
	e = (t_env*)malloc(sizeof(t_env));
	init_mem(e, arg);
	va_start(list, format);
	if (!process_format(format, arg, list, e))
		return (0);
	va_end(list);
	ret = e->ret;
	destroy_mem(arg, e);
	return (ret);
}
