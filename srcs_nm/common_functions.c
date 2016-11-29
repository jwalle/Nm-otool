/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 19:09:58 by jwalle            #+#    #+#             */
/*   Updated: 2016/10/29 19:09:59 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	get_nsect(int n, t_nm_env *e)
{
	if (n == e->text)
		return ('t');
	else if (n == e->data)
		return ('d');
	else if (n == e->bss)
		return ('b');
	return ('s');
}

void	destroy_symbols(t_nm_env *e)
{
	int			i;

	i = 0;
	while (i < e->stocked)
	{
		free(e->all[i]->name);
		free(e->all[i]);
		i++;
	}
	free(e->all);
}

char	get_type(t_list64 *new, t_nm_env *e)
{
	char	c;
	char	mask;
	char	ret;

	c = new->n_type;
	mask = c & N_TYPE;
	ret = '?';
	if (mask == N_UNDF)
	{
		ret = 'u';
		if (new->value != 0)
			ret = 'c';
	}
	else if (mask == N_PBUD)
		ret = 'u';
	else if (mask == N_ABS)
		ret = 'a';
	else if (mask == N_INDR)
		ret = 'i';
	else if (mask == N_SECT)
		ret = get_nsect(new->n_sect, e);
	if ((c & N_EXT) && ret != '?')
		ret = ft_toupper(ret);
	return (ret);
}

void	print_default(t_nm_env *e)
{
	int i = 0;

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
			if (e->dylink && e->cpu == 64)
				ft_printf("%08x%08x", 0x0000ffff - 0x8000, e->all[i]->value);
			else if (e->lib || (e->cpu == 32 && e->fat == 1))
				ft_printf("%08x%08x", 0, e->all[i]->value);
			else if (e->cpu == 64)
				ft_printf("%08x%08x", 1, e->all[i]->value);
			else if (e->cpu == 32)
				ft_printf("%08x", e->all[i]->value);
			ft_printf(" %c %s\n", e->all[i]->type, e->all[i]->name);
		}
		i++;
	}
}

void	print_x(t_nm_env *e)
{
	int i = 0;

	while (i < e->stocked)
	{
		if (e->all[i]->type == 'U')
		{
			if (e->cpu == 32 && !e->fat)
				ft_printf("%08x", 0);
			else if (e->cpu == 64 || e->cpu == 16 || e->fat)
				ft_printf("%016x", 0);
			ft_printf(" %02x %02x %04x %08x %s\n", e->all[i]->n_type, e->all[i]->n_sect, e->all[i]->n_desc, e->all[i]->strx, e->all[i]->name);		
		}
		else if (ft_strchr(SYMBOLS, e->all[i]->type))
		{
			if (e->dylink && e->cpu == 64)
				ft_printf("%08x%08x", 0x0000ffff - 0x8000, e->all[i]->value);
			else if (e->lib || (e->cpu == 32 && e->fat == 1))
				ft_printf("%08x%08x", 0, e->all[i]->value);
			else if (e->cpu == 64)
				ft_printf("%08x%08x", 1, e->all[i]->value);
			else if (e->cpu == 32)
				ft_printf("%08x", e->all[i]->value);
			ft_printf(" %02x %02x %04x %08x %s\n", e->all[i]->n_type, e->all[i]->n_sect, e->all[i]->n_desc, e->all[i]->strx, e->all[i]->name);
		}
		i++;
	}
}


void	print_output(t_nm_env *e) // CACA
{
	if (e->bonus == 'x')
		print_x(e);
	print_default(e);
}
