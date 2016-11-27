/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 16:10:23 by jwalle            #+#    #+#             */
/*   Updated: 2016/10/29 18:47:31 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/*
**	/usr/include/mach-o/...
*/

static	int	magic_number[] = { MH_MAGIC , MH_MAGIC_64, MH_RANLIB, FAT_CIGAM, FAT_MAGIC ,0};

void	(*magic_functions[])(char*, t_nm_env*) =
{ handle_stuff_32 , handle_stuff_64 , handle_stuff_library, handle_stuff_taf, handle_stuff_fat};
		
void	nm(char *ptr, t_nm_env *e)
{
	int				i;
	int				flag;
	int				magic_num;

	i = 0;
	flag = 0;
	magic_num = *(int *)ptr;
	// printf("magic_number = %#x\n", magic_num);
	while (magic_number[i])
	{
		if (magic_num == magic_number[i])
		{
			magic_functions[i](ptr, e);
			flag++;
		}
		i++;
	}
	// if (!flag)
		// ft_printf("ft_nm : %s : The file was not recognized as a valid object file.\n", e->file);
}

int		process_file(int fd, t_nm_env *e)
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
	nm(ptr, e);
	if (munmap(ptr, buf.st_size) < 0)
	{
		ft_printf("munmap error.\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_nm_env	*init_env(char *file)
{
	t_nm_env *e;

	e = (t_nm_env *)malloc(sizeof(t_nm_env));
	e->cpu = 0;
	e->fat = 0;
	e->lib = 0;
	e->text = 0;
	e->dylink = 0;
	e->data = 0;
	e->bss = 0;
	e->stocked = 0;
	e->file = ft_strdup(file);
	return (e);
}

void	clear_env(t_nm_env *e)
{
	free(e->file);
	free(e);
}

int		test_open(char *av)
{
	int			fd;
	t_nm_env	*e;

	e = NULL;
	if ((fd = open(av, O_RDONLY)) < 0)
	{
		ft_printf("%s : No such file or directory.\n", av);
		return(EXIT_FAILURE);
	}
	e = init_env(av);
	process_file(fd, e);
	clear_env(e);
	return (fd);
}

int		main(int ac, char **av)
{
	int 			fd;
	int				i;

	fd = 0;
	i = 1;

	if (ac == 1)
		test_open("a.out");
	else if (ac == 2)
		test_open(av[1]);
	else if (ac > 2)
	{
		while (i < ac)
		{
			printf("\n%s\n", av[i]); // REAL printf
			test_open(av[i]);
			i++;
		}
	}
	else
	{
		ft_printf("Usage :\n"); //todo
		return (EXIT_FAILURE);
	}
	return (0);
}
