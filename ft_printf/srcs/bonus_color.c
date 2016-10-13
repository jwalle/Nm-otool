/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 18:03:45 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/30 18:04:05 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_color(t_env *e, char *color)
{
	if (!ft_strcmp_ptf(color, "red"))
		ft_putstr_ret(e, "\x1b[31m");
	else if (!ft_strcmp_ptf(color, "green"))
		ft_putstr_ret(e, "\x1b[32m");
	else if (!ft_strcmp_ptf(color, "yellow"))
		ft_putstr_ret(e, "\x1b[33m");
	else if (!ft_strcmp_ptf(color, "blue"))
		ft_putstr_ret(e, "\x1b[34m");
	else if (!ft_strcmp_ptf(color, "magenta"))
		ft_putstr_ret(e, "\x1b[35m");
	else if (!ft_strcmp_ptf(color, "cyan"))
		ft_putstr_ret(e, "\x1b[36m");
	else if (!ft_strcmp_ptf(color, "grey"))
		ft_putstr_ret(e, "\x1b[37m");
	else if (!ft_strcmp_ptf(color, "eoc"))
		ft_putstr_ret(e, "\x1b[0m");
	else
		return (0);
	return (1);
}

int		process_color(t_env *e, const char *format)
{
	int		i;

	i = 0;
	while (format[i])
	{
		if (format[i] == '}')
		{
			if (print_color(e, ft_strndup((char *)format, i)) > 0)
				return (i + 2);
			else
				return (0);
		}
		i++;
	}
	return (0);
}
