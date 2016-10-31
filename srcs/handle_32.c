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
	DEBUG;
	printf("%d\n", array[i].n_un.n_strx);
	new->name = ft_strdup(st + array[i].n_un.n_strx);
	DEBUG;
	new->n_sect = array[i].n_sect;
	new->n_type = array[i].n_type;
	new->type = get_type(new, e);
	return (new);	
}

static void	stock_output_32(int nsyms, int symoff, int stroff, char *ptr, t_nm_env *e)
{
	int				i;
	int				j;
	char			*string_table;
	struct nlist	*array;
	t_list64		**all;

	i = 0;
	j = 0;
	array = (void *)ptr + symoff;
	string_table = (void *)ptr + stroff;
	all = (t_list64**)malloc(sizeof(t_list64*) * nsyms);
	e->all = all;
	while (i < nsyms)
	{
		if (array[i].n_un.n_strx > 1 && array[i].n_sect > 0)
		{
			DEBUG;
			all[j] = stock_symbols_32(array, string_table, i, e);
			DEBUG;
			j++;
			/*printf("plop = %s, %i, %i, %i, %i, (%d), [%d]\n", string_table + array[i].n_un.n_strx
													  , array[i].n_type & N_STAB
													  , array[i].n_type & N_PEXT
													  , array[i].n_type & N_TYPE
													  , array[i].n_type & N_EXT
													  , array[i].n_un.n_strx
													  , array[i].n_sect);*/
		
		}
		i++;
	}
	e->stocked = j;
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
	for (i = 0 ; ncmds > i ; ++i)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			stock_output_32(sym->nsyms, sym->symoff, sym->stroff, ptr, e);
			sort_output(e);
			print_output(e);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

static void	find_sector_and_segment_32(struct load_command *lc, t_nm_env *e)
{
	struct segment_command	*sg;
	struct section			*s;
	int						nsect;
	uint32_t				j;

	nsect = 0;
	sg = (struct segment_command *)lc;
	s = (struct section *)((char *)sg + sizeof(struct segment_command));
	for (j = 0; j < sg->nsects ; j++)
	{
		DEBUG;
		if (!ft_strcmp((s + j)->sectname, SECT_TEXT) &&
			!ft_strcmp((s + j)->segname, SEG_TEXT))
			e->text = nsect + 1;
		else if (!ft_strcmp((s + j)->sectname, SECT_DATA) &&
				!ft_strcmp((s + j)->segname, SEG_DATA))
			e->data = nsect + 1;
		else if (!ft_strcmp((s + j)->sectname, SECT_BSS) &&
				!ft_strcmp((s + j)->segname, SEG_DATA))
			e->bss = nsect + 1;
		//printf("(s + j)->sectname : %s\n", (s + j)->sectname);
		nsect++;
	}
}

void		handle_stuff_32(char *ptr, t_nm_env *e)
{
	unsigned int		i;
	int					nsect;
	struct mach_header	*header;
	struct load_command	*lc;
	
	nsect = 0;
	header = (struct mach_header*)ptr;
	DEBUG;
	lc = (void *)ptr + sizeof(*	header);
	for (i = 0 ; header->ncmds > i ; ++i)
	{		
		if (lc->cmd == LC_SEGMENT)
		{
			
			// ft_printf("%s, %d\n", sg->segname, sg->nsects);
			find_sector_and_segment_32(lc, e);
		}
		lc = (void *)lc + lc->cmdsize;
	}
	DEBUG ;
	handle_32(ptr, e);
	printf("32 !\n");
}
