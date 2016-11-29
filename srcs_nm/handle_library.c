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

void		print_library(void *ptr, struct ranlib *ran,
					unsigned int n, t_nm_env *e)
{
	while (n-- > 0)
	{
		if ((ran[n].ran_off != ran[n + 1].ran_off) &&
			!ft_strncmp(ptr + ran[n].ran_off, AR_EFMT1, ft_strlen(AR_EFMT1)))
		{
			ft_printf("\n%s(%s):\n", e->file,
				ptr + ran[n].ran_off + AR_HDR_SIZE);
			e->text = 0;
			e->data = 0;
			e->bss = 0;
			nm(ptr + ran[n].ran_off + AR_HDR_SIZE
				+ ft_atoi(ptr + ran[n].ran_off + 3), e);
		}
	}
}

void		sort_library(struct ranlib *ran, unsigned int n)
{
	unsigned int	i;
	unsigned int	j;
	struct ranlib	temp;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n - 1)
		{
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
}

void		handle_stuff_library(char *ptr, t_nm_env *e)
{
	int					hdr_sz;
	unsigned int		i;
	struct ranlib		*ran;

	hdr_sz = 0;
	e->lib = 1;
	if (ft_strcmp(ptr + SARMAG + AR_HDR_SIZE, SYMDEF) &&
		ft_strcmp(ptr + SARMAG + AR_HDR_SIZE, SYMDEF_SORTED))
		return ;
	hdr_sz = ft_atoi(ptr + SARMAG + ft_strlen(AR_EFMT1)) + AR_HDR_SIZE + SARMAG;
	i = *(int *)(ptr + hdr_sz) / sizeof(struct ranlib);
	ran = (struct ranlib *)malloc(RAN_SIZE * i);
	while (i-- > 0)
		ran[i] = *(struct ranlib *)(ptr + hdr_sz + 4 + i * (RAN_SIZE));
	i = *(int *)(ptr + hdr_sz) / sizeof(struct ranlib);
	sort_library(ran, i);
	print_library(ptr, ran, i, e);
	free(ran);
}
