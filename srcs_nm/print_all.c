/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 14:09:27 by jwalle            #+#    #+#             */
/*   Updated: 2016/11/29 14:09:31 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_sym_value(t_nm_env *e, int i)
{
	if (e->dylink && e->cpu == 64)
		ft_printf("%08x%08x", 0x0000ffff - 0x8000, e->all[i]->value);
	else if (e->lib || (e->cpu == 32 && e->fat == 1))
		ft_printf("%08x%08x", 0, e->all[i]->value);
	else if (e->cpu == 64)
		ft_printf("%08x%08x", 1, e->all[i]->value);
	else if (e->cpu == 32)
		ft_printf("%08x", e->all[i]->value);
}

void	print_default(t_nm_env *e)
{
	int i;

	i = 0;
	while (i < e->stocked)
	{
		if (e->all[i]->type == 'U')
		{
			if (e->bonus != 'u')
			{
				if (e->cpu == 32 && !e->fat)
					ft_printf("%8.x", 0);
				else if (e->cpu == 64 || e->cpu == 16 || e->fat)
					ft_printf("        %8.x", 0);
				ft_printf(" %c %s\n"	, e->all[i]->type, e->all[i]->name);
			}
			else
				ft_printf("%s\n", e->all[i]->name);
		}
		else if (ft_strchr(SYMBOLS, e->all[i]->type) && e->bonus != 'u')
		{
			print_sym_value(e, i);
			ft_printf(" %c %s\n", e->all[i]->type, e->all[i]->name);
		}
		i++;
	}
}

void	print_x(t_nm_env *e)
{
	int i;

	i = 0;
	while (i < e->stocked)
	{
		if (e->all[i]->type == 'U')
		{
			if (e->cpu == 32 && !e->fat)
				ft_printf("%08x", 0);
			else if (e->cpu == 64 || e->cpu == 16 || e->fat)
				ft_printf("%016x", 0);
			ft_printf(" %02x %02x %04x %08x %s\n", e->all[i]->n_type,
				e->all[i]->n_sect, e->all[i]->n_desc, e->all[i]->strx,
				e->all[i]->name);
		}
		else if (ft_strchr(SYMBOLS, e->all[i]->type))
		{
			print_sym_value(e, i);
			ft_printf(" %02x %02x %04x %08x %s\n", e->all[i]->n_type,
				e->all[i]->n_sect, e->all[i]->n_desc, e->all[i]->strx,
				e->all[i]->name);
		}
		i++;
	}
}

void	print_output(t_nm_env *e)
{
	if (e->bonus == 'x')
		print_x(e);
	print_default(e);
}
