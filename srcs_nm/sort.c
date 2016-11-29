#include "ft_nm.h"

void	sort_reverse(t_nm_env *e)
{
	int			i;
	int			j;
	int			n;
	t_list64	*temp;

	i = 0;
	n = e->stocked;
	while (i < n)
	{
		j = 0;
		while (j < n - 1)
		{
			while (ft_strcmp(e->all[j]->name, e->all[j + 1]->name) < 0)
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

void	sort_num(t_nm_env *e)
{
	int			i;
	int			j;
	int			n;
	t_list64	*temp;

	i = 0;
	n = e->stocked;
	while (i < n)
	{
		j = 0;
		while (j < n - 1)
		{
			while (e->all[j]->value > e->all[j + 1]->value)
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

void	sort_default(t_nm_env *e)
{
	int			i;
	int			j;
	int			n;
	t_list64	*temp;

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

void	sort_output(t_nm_env *e)
{
	if (e->bonus == 'p')
		return ;
	else if (e->bonus == 'r')
		sort_reverse(e);
	else if (e->bonus == 'n')
		sort_num(e);
	else
		sort_default(e);
}
