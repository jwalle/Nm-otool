/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 18:55:02 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/19 18:55:27 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_int_octal_len(unsigned long long n)
{
	int i;

	i = 0;
	while (n)
	{
		n /= 8;
		i++;
	}
	return (i);
}

int	ft_int_hex_len(unsigned long long n)
{
	int i;

	i = 0;
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}

int	ft_intlen(int n)
{
	int i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_ll_intlen(unsigned long long n)
{
	int i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_parse_len(unsigned long long n, char spe)
{
	if (n == 0)
		return (1);
	if (spe == 'o')
		return (ft_int_octal_len(n));
	if (spe == 'x' || spe == 'X')
		return (ft_int_hex_len(n));
	return (ft_ll_intlen(n));
}
