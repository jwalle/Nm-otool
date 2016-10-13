/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 19:51:55 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/19 19:51:57 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putllunbr(t_env *e, unsigned long long int n)
{
	if (n < 10)
		ft_putchar_ret(e, n + '0');
	else if (n >= 10)
	{
		ft_putllunbr(e, n / 10);
		ft_putllunbr(e, n % 10);
	}
}

void	ft_putnbr_octal(t_env *e, unsigned long long number)
{
	char				*octal;
	int					i;

	if (number == 0)
	{
		ft_putchar_ret(e, '0');
		return ;
	}
	i = ft_int_octal_len(number);
	octal = ft_strnew_ptf(i);
	while (number)
	{
		octal[--i] = number % 8 + '0';
		number = number / 8;
	}
	ft_putstr_ret(e, octal);
	free(octal);
}

void	ft_putnbr_hexa(t_env *e, unsigned long long number, char spe)
{
	char				*base;
	char				*hex;
	int					i;

	if (number == 0)
	{
		ft_putchar_ret(e, '0');
		return ;
	}
	if (spe == 'x')
		base = HEXA;
	if (spe == 'X')
		base = HEXA_MAJ;
	i = ft_int_hex_len(number);
	hex = ft_strnew_ptf(i);
	while (number)
	{
		hex[--i] = base[number % 16];
		number = number / 16;
	}
	ft_putstr_ret(e, hex);
	free(hex);
}
