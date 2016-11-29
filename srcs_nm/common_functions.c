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

t_nm_env	*init_env(char *file, char bonus)
{
	t_nm_env	*e;

	e = (t_nm_env *)malloc(sizeof(t_nm_env));
	e->cpu = 0;
	e->fat = 0;
	e->lib = 0;
	e->text = 0;
	e->dylink = 0;
	e->data = 0;
	e->bss = 0;
	e->stocked = 0;
	e->bonus = bonus;
	e->file = ft_strdup(file);
	return (e);
}

char		get_bonus(char *av)
{
	if (!ft_strcmp("-x", av))
		return ('x');
	else if (!ft_strcmp("-r", av))
		return ('r');
	else if (!ft_strcmp("-p", av))
		return ('p');
	else if (!ft_strcmp("-n", av))
		return ('n');
	else if (!ft_strcmp("-u", av))
		return ('u');
	ft_printf("%s is not a valid attribute\n", av);
	return (0);
}

char		get_nsect(int n, t_nm_env *e)
{
	if (n == e->text)
		return ('t');
	else if (n == e->data)
		return ('d');
	else if (n == e->bss)
		return ('b');
	return ('s');
}

void		destroy_symbols(t_nm_env *e)
{
	int			i;

	i = 0;
	while (i < e->stocked)
	{
		free(e->all[i]->name);
		free(e->all[i]);
		i++;
	}
	free(e->all);
}

char		get_type(t_list64 *new, t_nm_env *e)
{
	char	c;
	char	mask;
	char	ret;

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
	else if (mask == N_INDR)
		ret = 'i';
	else if (mask == N_SECT)
		ret = get_nsect(new->n_sect, e);
	if ((c & N_EXT) && ret != '?')
		ret = ft_toupper(ret);
	return (ret);
}
