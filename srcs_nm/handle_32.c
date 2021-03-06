/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 18:42:55 by jwalle            #+#    #+#             */
/*   Updated: 2016/10/29 18:44:05 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_list64	*stock_symbols_32(struct nlist *array, char *st, int i, t_nm_env *e)
{
	t_list64	*new;

	if (!(new = malloc(sizeof(t_list64))))
		return (NULL);
	new->value = array[i].n_value;
	new->name = ft_strdup(st + array[i].n_un.n_strx);
	new->n_sect = array[i].n_sect;
	new->n_desc = array[i].n_desc;
	new->n_type = array[i].n_type;
	new->strx = array[i].n_un.n_strx;
	new->type = get_type(new, e);
	return (new);
}

static void	stock_output_32(struct symtab_command *sym, char *ptr, t_nm_env *e)
{
	int				i;
	char			*string_table;
	struct nlist	*array;
	t_list64		**all;

	i = 0;
	array = (void *)ptr + sym->symoff;
	string_table = (void *)ptr + sym->stroff;
	all = (t_list64**)malloc(sizeof(t_list64*) * sym->nsyms);
	e->all = all;
	while (i < (int)sym->nsyms)
	{
		if (array[i].n_un.n_strx >= 1 && array[i].n_sect >= 0)
		{
			if (ft_strlen(string_table + array[i].n_un.n_strx)
				&& !ft_strstr(string_table + array[i].n_un.n_strx, "radr"))
				all[e->stocked++] = stock_symbols_32(array, string_table, i, e);
		}
		i++;
	}
}

static void	handle_32(char *ptr, t_nm_env *e)
{
	int						i;
	int						ncmds;
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	header = (struct mach_header *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	i = 0;
	while (ncmds > ++i)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			stock_output_32(sym, ptr, e);
			sort_output(e);
			print_output(e);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

static int	find_sec_and_seg_32(struct load_command *lc, t_nm_env *e, int nsect)
{
	struct segment_command	*sg;
	struct section			*s;
	uint32_t				j;

	sg = (struct segment_command *)lc;
	s = (struct section *)((char *)sg + sizeof(struct segment_command));
	j = 0;
	while (j < sg->nsects)
	{
		if (!ft_strcmp((s + j)->sectname, SECT_TEXT) &&
			!ft_strcmp((s + j)->segname, SEG_TEXT))
			e->text = nsect;
		else if (!ft_strcmp((s + j)->sectname, SECT_DATA) &&
				!ft_strcmp((s + j)->segname, SEG_DATA))
			e->data = nsect;
		else if (!ft_strcmp((s + j)->sectname, SECT_BSS) &&
				!ft_strcmp((s + j)->segname, SEG_DATA))
			e->bss = nsect;
		j++;
		nsect++;
	}
	return (nsect);
}

void		handle_stuff_32(char *ptr, t_nm_env *e)
{
	unsigned int		i;
	int					nsect;
	struct mach_header	*header;
	struct load_command	*lc;

	i = 0;
	nsect = 1;
	header = (struct mach_header*)ptr;
	lc = (void *)ptr + sizeof(*header);
	if (!e->cpu)
		e->cpu = 32;
	e->lib = 0;
	while (header->ncmds > ++i)
	{
		if (lc->cmd == LC_SEGMENT)
			nsect = find_sec_and_seg_32(lc, e, nsect);
		lc = (void *)lc + lc->cmdsize;
	}
	handle_32(ptr, e);
	destroy_symbols(e);
}
