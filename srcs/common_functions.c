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

char		get_type(struct nlist_64 *array, int i, t_nm_env *e)
{
	char	c;
	char	mask;
	char	ret;
	int		n;

	n = array[i].n_sect;
	c = array[i].n_type;
	mask = c & N_TYPE;
	ret = '?';

	if (mask == N_UNDF)
	{
		ret = 'u';
		if (array[i].n_value != 0)
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

t_list64	*stock_symbols(struct nlist_64 *array, char *st, int i, t_nm_env *e)
{
	t_list64	*new;

	if (!(new = malloc(sizeof(t_list64))))
		return (NULL);
	new->value = array[i].n_value;
	new->name = ft_strdup(st + array[i].n_un.n_strx);
	new->type = get_type(array, i, e);
	new->n_sect = array[i].n_sect;
	return (new);	
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
			while (ft_strcmp(e->all[j]->name, e->all[j + 1]->name) > 0	)
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

void	stock_output(int nsyms, int symoff, int stroff, char *ptr, t_nm_env *e)
{
	int				i;
	int				j;
	char			*string_table;
	struct nlist_64	*array;
	t_list64		**all;

	i = 0;
	j = 0;
	array = (void *)ptr + symoff;
	string_table = (void *)ptr + stroff;
	all = (t_list64**)malloc(sizeof(t_list64*) * nsyms);
	e->all = all;
	while (i < nsyms)
	{
		if (array[i].n_un.n_strx > 1)
		{
			all[j] = stock_symbols(array, string_table, i, e);
			j++;
			/*printf("plop = %s, %i, %i, %i, %i, (%d), [%d]\n", string_table + array[i].n_un.n_strx
													  , array[i].n_type & N_STAB
													  , array[i].n_type & N_PEXT
													  , array[i].n_type & N_TYPE
													  , array[i].n_type & N_EXT
													  , array[i].n_un.n_strx
													  , array[i].n_sect);*/
		
		}
		i++;
	}
	e->stocked = j;
}

void	print_output(t_nm_env *e)
{
	int				i;

	i = 0;
	while(i < e->stocked)
	{
		if (e->all[i]->type == 'U' || e->all[i]->type == 'u')
			printf("%16.x %c %s\n", 0, e->all[i]->type, e->all[i]->name);
		//else if (e->all[i]->type == '?' && e->all[i]->value != 0)
		//	printf("%016x %c %s\n", e->all[i]->n_sect, e->all[i]->type, e->all[i]->name);
		else if (e->all[i]->type == 'T' || e->all[i]->type == 't' || e->all[i]->type == 's' || e->all[i]->type == 'S' || e->all[i]->type == 'd' || e->all[i]->type == 'D' || e->all[i]->type == 'b' || e->all[i]->type == 'b')
			printf("%08x%08x %c %s\n",1 , e->all[i]->value, e->all[i]->type, e->all[i]->name);
		//else
		//	printf("%016x %c %s <------------\n", e->all[i]->value, e->all[i]->type, e->all[i]->name);
		i++;
	}
}
