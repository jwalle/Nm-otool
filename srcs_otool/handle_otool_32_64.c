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

static int	find_sector_and_segment_32(char *ptr, struct load_command *lc,
	t_otool_env *e, int nsect)
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
		{
			print_otool(s->size, s->addr, ptr + s->offset, e);
			return (0);
		}
		nsect++;
		j++;
	}
	return (nsect);
}

void		handle_otool_32(char *ptr, t_otool_env *e)
{
	int						nsect;
	struct mach_header		*header;
	struct load_command		*lc;

	nsect = 1;
	header = (struct mach_header*)ptr;
	lc = (void *)ptr + sizeof(*header);
	if (!e->cpu)
		e->cpu = 32;
	if (header->filetype == MH_DYLIB || header->filetype == MH_OBJECT)
		e->lib = 1;
	if (header->filetype == MH_BUNDLE)
		e->bundle = 1;
	if (header->filetype == MH_DYLINKER)
		e->dylink = 1;
	while (header->ncmds--)
	{
		if (lc->cmd == LC_SEGMENT)
			nsect = find_sector_and_segment_32(ptr, lc, e, nsect);
		lc = (void *)lc + lc->cmdsize;
	}
}

static int	find_sector_and_segment_64(char *ptr, struct load_command *lc,
	t_otool_env *e, int nsect)
{
	struct segment_command_64	*sg;
	struct section_64			*s;
	uint32_t					j;

	j = 0;
	sg = (struct segment_command_64 *)lc;
	s = (struct section_64 *)((char *)sg + sizeof(struct segment_command_64));
	while (j < sg->nsects)
	{
		if (!ft_strcmp((s + j)->sectname, SECT_TEXT) &&
			!ft_strcmp((s + j)->segname, SEG_TEXT))
		{
			print_otool(s->size, s->addr, ptr + s->offset, e);
			return (0);
		}
		nsect++;
		j++;
	}
	return (nsect);
}

void		handle_otool_64(char *ptr, t_otool_env *e)
{
	int						nsect;
	struct mach_header_64	*header;
	struct load_command		*lc;

	nsect = 1;
	header = (struct mach_header_64*)ptr;
	lc = (void *)ptr + sizeof(*header);
	if (!e->cpu)
		e->cpu = 64;
	if (header->filetype == MH_DYLIB)
		e->dylib = 1;
	if (header->filetype == MH_BUNDLE)
		e->bundle = 1;
	if (header->filetype == MH_OBJECT)
		e->obj = 1;
	if (header->filetype == MH_DYLINKER)
		e->dylink = 1;
	while (header->ncmds--)
	{
		if (lc->cmd == LC_SEGMENT_64)
			nsect = find_sector_and_segment_64(ptr, lc, e, nsect);
		lc = (void *)lc + lc->cmdsize;
	}
}
