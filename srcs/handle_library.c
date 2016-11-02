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

#define __LP64__ 1

void		handle_stuff_library(char *ptr, t_nm_env *e)
{
	unsigned int		i;
	char				*str;
	struct ar_hdr		*ar;
	struct ranlib		*ran;
	// struct ranlib		*rlib;

	i = 0;
	int start = 60 + 6 + 494;

	start = 0;


	//str = strndup(ptr, SARMAG);
	// puts(str);
	str = (void *)ptr + SARMAG + 60;
	if (!ft_strcmp(str, SYMDEF_SORTED))
		puts("SYMDEF !!!!!!!!!!");
	ran = (void*)str + ft_strlen(SYMDEF_SORTED);
	//ran = (struct ranlib*)ran + 1;
	
	ar = (void *)ptr + SARMAG;

	ar = (struct ar_hdr*)ar + 10;
	
	while (i < 10000)
	{
		if (ptr[i + start] == 0)
			ft_putchar('0');
		else if (isprint(ptr[i + start]))
			ft_putchar(ptr[i + start]);
		else
			ft_putchar('.');
		i++;
	}
	i = 59;
	while (--i > 0)
	printf("\nran : %s\n",ptr + ran[i].ran_off + sizeof(struct ar_hdr));

	//printf("\nran : %s\n", ran[0].ran_un.stroff);
	//printf("\nar->name : %s, time : %d\n", ar->ar_name, (int)ar->ar_gid);
	//printf("PLOLOLOOOLLP\n");
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
