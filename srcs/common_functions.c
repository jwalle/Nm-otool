/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 19:09:58 by jwalle            #+#    #+#             */
/*   Updated: 2016/10/29 19:09:59 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	get_type(t_list64 *new, t_nm_env *e)
{
	char	c;
	char	mask;
	char	ret;
	int		n;

	n = new->n_sect;
	c = new->n_type;
	mask = c & N_TYPE;
	ret = '?';
	if (mask == N_UNDF)
	{
		ret = 'u';
		if (new->value != 0)
			ret = 'c';
	}
	else if (mask == N_PBUD)
		ret = 'u';
	else if (mask == N_ABS)
		ret = 'a';
	else if (mask == N_SECT)
	{
		if (n == e->text)
			ret = 't';
		else if (n == e->data)
			ret = 'd';
		else if (n == e->bss)
			ret = 'b';
		else
			ret = 's';
	}
	if ((c & N_EXT) && ret != '?')
		ret = ft_toupper(ret);
	return (ret);
}

void	print_output(t_nm_env *e)
{
	int				i;

	i = 0;
	while(i < e->stocked)
	{
		if (e->all[i]->type == 'U' && e->all[i]->type == 'u' && e->cpu == 64)
			ft_printf("");
		if (e->all[i]->type == 'U' /*|| e->all[i]->type == 'u'*/)
		{
			if (e->cpu == 32)
				ft_printf("%8.x %c %s\n", 0, e->all[i]->type, e->all[i]->name);
			else if (e->cpu == 64 || e->cpu == 16)
				ft_printf("        %8.x %c %s\n", 0, e->all[i]->type, e->all[i]->name);
		}
		//else if (e->all[i]->type == '?' && e->all[i]->value != 0)
		//	printf("%016x %c %s\n", e->all[i]->n_sect, e->all[i]->type, e->all[i]->name);
		else if (e->all[i]->type == 'T' || e->all[i]->type == 't' || e->all[i]->type == 's'
			|| e->all[i]->type == 'S' || e->all[i]->type == 'd' || e->all[i]->type == 'D'
			|| e->all[i]->type == 'b' || e->all[i]->type == 'b')
		{
			if (e->cpu == 64)
				ft_printf("00000001%08x %c %s\n" , e->all[i]->value, e->all[i]->type, e->all[i]->name);
			else if (e->cpu == 16)
				ft_printf("00000000%08x %c %s\n" , e->all[i]->value, e->all[i]->type, e->all[i]->name);
			else if (e->cpu == 32)
			ft_printf("%08x %c %s\n" , e->all[i]->value, e->all[i]->type, e->all[i]->name);
		}
		// else
			// printf("%016x %c %s <------------\n", e->all[i]->value, e->all[i]->type, e->all[i]->name);
		i++;
	}
}


void	sort_output(t_nm_env *e)
{
	int	i;
	int	j;
	int n;
	t_list64 *temp;

	i = 0;
	n = e->stocked;
	while (i < n)
	{
		j = 0;
		while (j < n - 1)
		{
			while (ft_strcmp(e->all[j]->name, e->all[j + 1]->name) > 0)
			{
				 temp = e->all[j + 1];
				 e->all[j + 1] = e->all[j];
				 e->all[j] = temp;
			}
			j++;
		}
		i++;
	}
}

