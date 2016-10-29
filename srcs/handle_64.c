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
			stock_output(sym->nsyms, sym->symoff, sym->stroff, ptr, e);
			sort_output(e);
			print_output(e);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

void	handle_stuff_64(char *ptr, t_nm_env *e)
{
	int						i;
	uint32_t				j;
	int						nsect;
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct segment_command_64	*sg;
	struct section_64			*s;
	
	nsect = 0;
	header = (struct mach_header_64*)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*	header);
	for (i = 0 ; ncmds > i ; ++i)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			sg = (struct segment_command_64 *)lc;
			//printf("%s, %d\n", sg->segname, sg->nsects);
			s = (struct section_64 *)((char *)sg + sizeof(struct segment_command_64));
			for (j = 0; j < sg->nsects ; j++)
			{
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
		lc = (void *)lc + lc->cmdsize;
	}
	handle_64(ptr, e);
}


