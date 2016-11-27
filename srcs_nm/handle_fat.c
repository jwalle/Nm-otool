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

	ret = ((n & 0x000000ff) << 24 |
		(n & 0x0000ff00) << 8|
		(n & 0x00ff0000) >> 8|
		(n & 0xff000000) >> 24);
	return(ret);
}

void		handle_stuff_taf(char *ptr, t_nm_env *e)
{
	int						i;
	struct fat_header		*header;
	struct fat_arch			*fat;

	e->fat = 1;
	header = (struct fat_header*)ptr;
	i = 0;
	fat = (struct fat_arch*)(ptr + sizeof(struct fat_header));
	while (swap_int_end(header->nfat_arch) > i++)
	{
		if (swap_int_end(fat->cputype) == CPU_TYPE_X86_64/* ||
			swap_int_end(fat->cputype) == CPU_TYPE_I386*/)
		{
			nm(ptr + swap_int_end(fat->offset),e);
			return ;
		}
		fat = (struct fat_arch*)((char*)fat + sizeof(struct fat_arch));	
	}
}

void		handle_stuff_fat(char *ptr, t_nm_env *e)
{
	int						i;
	struct fat_header		*header;
	struct fat_arch			*fat;

	e->fat = 1;
	header = (struct fat_header*)ptr;
	i = 0;
	fat = (struct fat_arch*)(ptr + sizeof(struct fat_header));
	while ((int)header->nfat_arch > i++)
	{
		if (fat->cputype == CPU_TYPE_X86_64 || fat->cputype == CPU_TYPE_I386)
		{
			nm(ptr + fat->offset,e);
			return ;
		}
		fat = (struct fat_arch*)((char*)fat + sizeof(struct fat_arch));	
	}
}