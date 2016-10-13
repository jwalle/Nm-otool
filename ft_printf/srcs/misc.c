/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 17:34:38 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/19 19:51:36 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_ret(t_env *e, char c)
{
	write(1, &c, 1);
	e->ret++;
}

void	ft_putstr_ret(t_env *e, const char *s)
{
	int i;

	i = 0;
	while (s[i])
		ft_putchar_ret(e, s[i++]);
}
