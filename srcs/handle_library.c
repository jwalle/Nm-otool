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

#define AR_HDR_SIZE	sizeof(struct ar_hdr)
#define RAN_SIZE sizeof(struct ranlib)

void		print_library(void *ptr, struct ranlib *ran, unsigned int n, t_nm_env *e)
{
	while (--n > 0)
	{
		ft_printf("filename.a(%s):\n", ptr + ran[n].ran_off + AR_HDR_SIZE);
		nm(ptr + ran[n].ran_off + 80, e);
		ft_putchar('\n');

	}
}

void		sort_library(void *ptr, struct ranlib *ran, unsigned int n)
{
	unsigned int i;
	unsigned int j;
	struct ranlib temp;

	printf("sorting :\n");

	i = 0;
	// printf("name : %s\n", ptr + ran[i - 1].ran_off + AR_HDR_SIZE);
	while (i < n)
	{
		j = 0;
		while(j < n - 1)
		{
			while (ft_strcmp(ptr + ran[j].ran_off + AR_HDR_SIZE, ptr + ran[j + 1].ran_off + AR_HDR_SIZE) > 0)
			{
				temp = ran[j + 1];
				ran[j + 1] = ran[j];
				ran[j] = temp;
			}
			j++;
		}
		i++;
	}
	printf("end of sorting\n");

}

void		handle_stuff_library(char *ptr, t_nm_env *e)
{
	int					hdr_size;
	unsigned int		i;
	struct ranlib		*ran;
	int					start;

	i = 0;
	hdr_size = 0;
	start = 0;


	// str = (void *)ptr + SARMAG + AR_HDR_SIZE;
	if (!ft_strcmp(ptr + SARMAG + AR_HDR_SIZE, SYMDEF) ||
		!ft_strcmp(ptr + SARMAG + AR_HDR_SIZE, SYMDEF_SORTED))
	{
		printf("PLOP\n");
	}
	hdr_size = ft_atoi(ptr + SARMAG + ft_strlen(AR_EFMT1)) + AR_HDR_SIZE + SARMAG;
	i = *(int *)(ptr + hdr_size) / sizeof(struct ranlib);
	ran = (struct ranlib *)malloc(RAN_SIZE * hdr_size);
	while (--i > 0)
	{
		ran[i] =  *(struct ranlib *)(ptr + hdr_size + 4 + i * (RAN_SIZE));
		(void)e;
	}
	i = *(int *)(ptr + hdr_size) / sizeof(struct ranlib);
	//sort_library(ptr, ran, i);
	print_library(ptr, ran, i, e);
	printf("suze : %lu\n", SARMAG + AR_HDR_SIZE);
	printf("Library !\n");
}
