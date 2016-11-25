/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 18:42:55 by jwalle            #+#    #+#             */
/*   Updated: 2016/10/29 18:44:05 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_list64	*stock_symbols_64(struct nlist_64 *array, char *st, int i, t_nm_env *e)
{
	t_list64	*new;

	if (!(new = malloc(sizeof(t_list64))))
		return (NULL);	
	new->value = array[i].n_value;
	new->name = ft_strdup(st + array[i].n_un.n_strx);
	new->n_sect = array[i].n_sect;
	new->n_type = array[i].n_type;
	new->type = get_type(new, e);

	//printf("name : %s, type : %c, mask : %d\n", new->name, new->type, new->n_type & N_TYPE);

	return (new);	
}

static void	stock_output_64(int nsyms, int symoff, int stroff, char *ptr, t_nm_env *e)
{
	int				i;
	int				j;
	char			*string_table;
	struct nlist_64	*array;
	t_list64		**all;

	i = 0;
	j = 0;
	array = (void *)ptr + symoff;
	string_table = (void *)ptr + stroff;
	all = (t_list64**)malloc(sizeof(t_list64*) * nsyms);
	e->all = all;
	while (i < nsyms)
	{
		if (array[i].n_un.n_strx >= 1 && array[i].n_sect >= 0) // added '=' for library ; deleted for /bin/htop
		{
			if (ft_strlen(string_table + array[i].n_un.n_strx) && !strstr(string_table + array[i].n_un.n_strx,"radr"))
			{
				all[j] = stock_symbols_64(array, string_table, i, e);
				j++;
			}
		/*	printf("plop = %s, %i, %i, %i, %i, (%d), [%d]\n", string_table + array[i].n_un.n_strx
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

static void	handle_64(char *ptr, t_nm_env *e)
{
	int						i;
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	
	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	for (i = 0 ; ncmds > i ; ++i)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			stock_output_64(sym->nsyms, sym->symoff, sym->stroff, ptr, e);
			sort_output(e);
			print_output(e);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

static int	find_sector_and_segment_64(struct load_command *lc, t_nm_env *e, int nsect)
{
	struct segment_command_64	*sg;
	struct section_64			*s;
	//int							nsect;
	uint32_t					j;

	//	nsect = 1;
	sg = (struct segment_command_64 *)lc;
	s = (struct section_64 *)((char *)sg + sizeof(struct segment_command_64));
	for (j = 0; j < sg->nsects ; j++)
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
		// printf("(s + j)->sectname : %s --> nsect = %d\n", (s + j)->sectname, nsect);
		nsect++;
	}
	return (nsect);
}

void		handle_stuff_64(char *ptr, t_nm_env *e)
{
	unsigned int			i;
	int						nsect;
	struct mach_header_64	*header;
	struct load_command		*lc;
	
	nsect = 1;
	header = (struct mach_header_64*)ptr;
	lc = (void *)ptr + sizeof(*	header);
	if (!e->cpu)
		e->cpu = 64;
	if (header->filetype == MH_DYLIB || header->filetype == MH_OBJECT)
		e->lib = 1;
	if (header->filetype == MH_DYLINKER)
		e->dylink = 1;
	for (i = 0 ; header->ncmds > i ; ++i)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			 // ft_printf("%s, %d\n", sg->segname, sg->nsects);
			//printf("PLOP\n");
			nsect = find_sector_and_segment_64(lc, e, nsect);
		}
		lc = (void *)lc + lc->cmdsize;
	}
	handle_64(ptr, e);
	// printf("data = %d\n", e->data);
	// printf("64 !\n");
}
