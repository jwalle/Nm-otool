/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 17:29:02 by jwalle            #+#    #+#             */
/*   Updated: 2016/11/25 17:29:47 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static	int	g_magic_number[] = { MH_MAGIC, MH_MAGIC_64, MH_RANLIB,
	FAT_CIGAM, FAT_MAGIC, 0};

void	(*g_magic_functions[])(char*, t_otool_env*) =
{handle_otool_32, handle_otool_64, handle_otool_library,
	handle_otool_taf, handle_otool_fat};

void		ft_otool(char *ptr, t_otool_env *e)
{
	int				i;
	int				flag;
	int				magic_num;

	i = 0;
	flag = 0;
	magic_num = *(int *)ptr;
	while (g_magic_number[i])
	{
		if (magic_num == g_magic_number[i])
		{
			g_magic_functions[i](ptr, e);
			flag++;
		}
		i++;
	}
}

int			process_file(int fd, t_otool_env *e)
{
	struct stat		buf;
	char			*ptr;

	if ((fstat(fd, &buf)) < 0)
	{
		ft_printf("fstat error.\n");
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
	{
		ft_printf("mmap error.\n");
		return (EXIT_FAILURE);
	}
	ft_otool(ptr, e);
	if (munmap(ptr, buf.st_size) < 0)
	{
		ft_printf("munmap error.\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_otool_env	*init_env(char *file)
{
	t_otool_env *e;

	e = (t_otool_env *)malloc(sizeof(t_otool_env));
	e->cpu = 0;
	e->fat = 0;
	e->lib = 0;
	e->obj = 0;
	e->bundle = 0;
	e->dylink = 0;
	e->dylib = 0;
	e->file = ft_strdup(file);
	return (e);
}

int			test_open(char *av)
{
	int			fd;
	t_otool_env	*e;

	e = NULL;
	if ((fd = open(av, O_RDONLY)) < 0)
	{
		ft_printf("%s : No such file or directory.\n", av);
		return (EXIT_FAILURE);
	}
	e = init_env(av);
	process_file(fd, e);
	free(e->file);
	free(e);
	return (fd);
}

int			main(int ac, char **av)
{
	int	fd;
	int	i;

	fd = 0;
	i = 1;
	if (ac == 1)
		ft_printf("Usage: ft_otool <object file> ...\n");
	else if (ac == 2)
		test_open(av[1]);
	else if (ac > 2)
	{
		while (i < ac)
			test_open(av[i++]);
	}
	return (0);
}
