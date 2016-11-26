/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_otool_32_64.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 12:10:23 by jwalle            #+#    #+#             */
/*   Updated: 2016/11/26 12:10:25 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int	find_sector_and_segment_32(char *ptr, struct load_command *lc, t_otool_env *e, int nsect)
{
	struct segment_command	*sg;
	struct section			*s;
	uint32_t					j;

	sg = (struct segment_command *)lc;
	s = (struct section *)((char *)sg + sizeof(struct segment_command));
	for (j = 0; j < sg->nsects ; j++)
	{
		if (!ft_strcmp((s + j)->sectname, SECT_TEXT) &&
			!ft_strcmp((s + j)->segname, SEG_TEXT))
		{
			print_dat_shit(s->size, s->addr, ptr + s->offset, e);
			return (0);
		}
		nsect++;
	}
	return (nsect);
}

void		handle_otool_32(char *ptr, t_otool_env *e)
{
	unsigned int			i;
	int						nsect;
	struct mach_header		*header;
	struct load_command		*lc;
	
	nsect = 1;
	header = (struct mach_header*)ptr;
	lc = (void *)ptr + sizeof(*	header);
	if (!e->cpu)
		e->cpu = 32;
	if (header->filetype == MH_DYLIB || header->filetype == MH_OBJECT || header->filetype == MH_BUNDLE)
		e->lib = 1;
	if (header->filetype == MH_DYLINKER)
		e->dylink = 1;
	for (i = 0 ; header->ncmds > i ; ++i)
	{
		if (lc->cmd == LC_SEGMENT)
			nsect = find_sector_and_segment_32(ptr, lc, e, nsect);
		lc = (void *)lc + lc->cmdsize;
	}
}

static int	find_sector_and_segment_64(char *ptr, struct load_command *lc, t_otool_env *e, int nsect)
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
		{
			print_dat_shit(s->size, s->addr, ptr + s->offset, e);
			return (0);
		}
		nsect++;
	}
	return (nsect);
}

void		handle_otool_64(char *ptr, t_otool_env *e)
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
	if (header->filetype == MH_DYLIB || header->filetype == MH_OBJECT || header->filetype == MH_BUNDLE)
		e->lib = 1;
	if (header->filetype == MH_DYLINKER)
		e->dylink = 1;
	for (i = 0 ; header->ncmds > i ; ++i)
	{
		if (lc->cmd == LC_SEGMENT_64)
			nsect = find_sector_and_segment_64(ptr, lc, e, nsect);
		lc = (void *)lc + lc->cmdsize;
	}
}
