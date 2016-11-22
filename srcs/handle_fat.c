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

int			swap_short_end(int n)
{
	int		ret;

	ret = ((n>>24)&0xff) |
		((n<<8)&0xff0000) |
		((n<<4)&0xff00) |
		((n<<24)&0xff000000);
	return(ret);
}

int			swap_int_end(int n)
{
	int		ret;

	ret = ((n>>24)&0xff) |
		((n<<8)&0xff0000) |
		((n<<4)&0xff00) |
		((n<<24)&0xff000000);
	return(ret);
}

void		handle_stuff_taf(char *ptr, t_nm_env *e)
{
	int						i;
	struct fat_header		*header;
	struct fat_arch			*fat;

	int magic_num = 0;

	
	header = (struct fat_header*)ptr;
	if (!e->cpu)
		e->cpu = 8;
	fat = (struct fat_arch*)(ptr + sizeof(struct fat_header));

	int n = 0;
	while (n <= 5000)
	{
		// if ((int)ptr[n] < 255)
			printf("%x", (char)ptr[n]);
		if (n % 100 == 0)
			printf("\nligne(%d):", n);
		n++;	
	}
	printf("\n");
	for (i = 0 ; swap_int_end(header->nfat_arch) > i ; ++i)
	{
		//if (fat->cputype == CPU_MAC)
		magic_num = *(int *)ptr + swap_int_end(fat->offset);
	
		printf("offset(be) = %d\n", swap_int_end(fat->offset));
		printf("offset(se) = %d\n",fat->offset);

		printf("size(be) = %d\n", swap_int_end(fat->size));
		printf("size(se) = %d\n",fat->size);
	
		printf("align(be) = %d\n", swap_int_end(fat->align));
		printf("align(se) = %d\n",fat->align);

		printf("fat_num = %#x\n", magic_num);

		printf("CPU = %#x\n", swap_int_end(fat->cputype));

		// nm(ptr + swap_int_end(fat->offset),e);
		//if (fat->cmd == LC_SEGMENT_64)
		{	
			//ft_printf("%s, %d\n", sg->segname, sg->nsects);
		//	find_sector_and_segment_64(lc, e);
		}
		fat = (struct fat_arch*)((void*)fat + sizeof(struct fat_arch));	
	}
	// handle_fat(ptr, e);
	printf("taf!\n");
}
