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
	// printf("n = %d\n", n);
	// n  = 20;
	while (n-- > 0)
	{
		// printf("ran[n] = %d, ran[n + 1] = %d, n = %d\n", ran[n].ran_off, ran[n + 1].ran_off, n);
		if ((ran[n].ran_off != ran[n + 1].ran_off) &&
			!ft_strncmp(ptr + ran[n].ran_off ,AR_EFMT1, ft_strlen(AR_EFMT1)))
		{
				ft_putchar('\n');
			//ft_printf("size = %lu, wat : %s\n", ran[n].ran_off + AR_HDR_SIZE, ptr + ran[n].ran_off);
			ft_printf("%s(%s):\n", e->file, ptr + ran[n].ran_off + AR_HDR_SIZE);
				e->text = 0;
	e->data = 0;
	e->bss = 0;
			nm(ptr + ran[n].ran_off + AR_HDR_SIZE
				+ ft_atoi(ptr + ran[n].ran_off + 3), e);			
			// if (n)
		}
	}
}

void		sort_library(struct ranlib *ran, unsigned int n)
{
	unsigned int i;
	unsigned int j;
	struct ranlib temp;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n - 1)
		{
			//printf("ran[n] = %d, ran[n + 1] = %d, n = %d\n", ran[j].ran_off, ran[j + 1].ran_off, j);
			while (ran[j].ran_off < ran[j + 1].ran_off)
			{

				temp = ran[j + 1];
				ran[j + 1] = ran[j];
				ran[j] = temp;
			}	
			j++;
		}
		i++;
	}
	//printf("end of sorting\n");
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

	e->lib = 1;
	if (ft_strcmp(ptr + SARMAG + AR_HDR_SIZE, SYMDEF) &&
		ft_strcmp(ptr + SARMAG + AR_HDR_SIZE, SYMDEF_SORTED))
	{
		ft_printf("abort abort\n");
		exit(0); // NOPE
	}
	hdr_size = ft_atoi(ptr + SARMAG + ft_strlen(AR_EFMT1)) + AR_HDR_SIZE + SARMAG;
	i = *(int *)(ptr + hdr_size) / sizeof(struct ranlib);
	ran = (struct ranlib *)malloc(RAN_SIZE * i);
	while (i-- > 0)
	{
		ran[i] = *(struct ranlib *)(ptr + hdr_size + 4 + i * (RAN_SIZE));
		// ft_printf("ran = %u, name = %s\n", ran[i].ran_off , ptr + ran[i].ran_off + AR_HDR_SIZE);
	}
	// printf("sizeof = %lu\n", RAN_SIZE);
	i = *(int *)(ptr + hdr_size) / sizeof(struct ranlib);
	sort_library(ran, i);
	print_library(ptr, ran, i, e);
}
