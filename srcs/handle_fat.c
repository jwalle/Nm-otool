/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 11:24:58 by jwalle            #+#    #+#             */
/*   Updated: 2016/11/09 11:24:59 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#define CPU_MAC 0x01

int			swap_int_end(int n)
{
	int		ret;

	ret = ((n>>24)&0xff) |
		((n<<8)&0xff0000) |
		((n<<4)&0xff00) |
		((n<<24)&0xff000000);
	return(ret);
}

void		handle_stuff_fat(char *ptr, t_nm_env *e)
{
	int						i;
	struct fat_header		*header;
	struct fat_arch			*fat;
	
	header = (struct fat_header*)ptr;
	e->cpu = 8; // ?????
	fat = (void*)ptr + sizeof(struct fat_header);


	for (i = 0 ; swap_int_end(header->nfat_arch) > i ; ++i)
	{
		printf("PLOP PLOP\n");
		//if (fat->cputype == CPU_MAC)
	


		printf("CPU = %#x\n", swap_int_end(fat->cputype));

		// if (fat->cmd == LC_SEGMENT_64)
		{	

			// ft_printf("%s, %d\n", sg->segname, sg->nsects);
		//	find_sector_and_segment_64(lc, e);
		}
		fat = (void*)fat + swap_int_end(fat->offset);	
	}
	// handle_fat(ptr, e);
	printf("fat !\n");
}