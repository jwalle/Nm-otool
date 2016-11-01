/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_library.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 18:42:55 by jwalle            #+#    #+#             */
/*   Updated: 2016/10/29 18:44:05 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <mach/machine.h>

void		handle_stuff_library(char *ptr, t_nm_env *e)
{
	unsigned int		i;
	// struct ranlib		*rlib;
	struct fat_header		*f_header;
	struct mach_header_64	*m_header;
	// struct fat_arch			*arch;

	i = 0;

	f_header = (struct fat_header*)ptr;
	m_header = (struct mach_header_64*)ptr + sizeof(f_header);

	printf("ncmd = %d\n", m_header->ncmds);
	// arch = (struct fat_arch*)ptr + sizeof(header);
	// printf(" magic = %u\n", header->nfat_arch);
	// printf(" cpu = %u\n", arch->cputype);
	// nsect = 0;
	// header = (struct mach_header*)ptr;
	// lc = (void *)ptr + sizeof(*	header);
	// e->cpu = 32;
	// for (i = 0 ; header->ncmds > i ; ++i)
	// {		
	// 	if (lc->cmd == LC_SEGMENT)
	// 	{
			
	// 		// ft_printf("%s, %d\n", sg->segname, sg->nsects);
	// 		find_sector_and_segment_32(lc, e);
	// 	}
	// 	lc = (void *)lc + lc->cmdsize;
	// }
	// handle_32(ptr, e);
	(void)e;
	printf("Library !\n");
}
