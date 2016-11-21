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

static	int	magic_number[] = { MH_MAGIC , MH_MAGIC_64, MH_RANLIB, FAT_CIGAM ,0};

void	(*magic_functions	[])(char*, t_nm_env*) =
{ handle_stuff_32 , handle_stuff_64 , handle_stuff_library, handle_stuff_taf};
		
void	nm(char *ptr, t_nm_env *e)
{
	int				i;
	int				magic_num;

	i = 0;
	magic_num = *(int *)ptr;
	//printf("magic_number = %#x\n", magic_num);
	while (magic_number[i])
	{
		if (magic_num == magic_number[i])
		{
			magic_functions[i](ptr, e);
		}
		i++;
	}
	/*if (magic_num == MH_MAGIC_64)
	{
		puts("c'est du 64 !!");
		handle_stuff_64(ptr, e);
		//handle_64(ptr, e);
	}
	else if (magic_num == MH_MAGIC)
	{
		puts("c'est du 32 !!");
	}
	else if (magic_num == FAT_MAGIC)
	{
		puts("c'est du FAT !!");
	}
	else if (magic_num == FAT_CIGAM)
	{
		puts("c'est du FAT_CIGAM... ? !!");
	}*/
}

int		process_file(int fd, t_nm_env *e)
{
	struct stat		buf;
	char			*ptr;


	if ((fstat(fd, &buf)) < 0)
	{
		perror("fstat");
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		perror("mmap");
		return (EXIT_FAILURE);
	}
	nm(ptr, e);
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
	int 			fd;
	t_nm_env		*e;

	fd = 0;
	e = (t_nm_env *)malloc(sizeof(t_nm_env));
	e->cpu = 0;
		// return (EXIT_FAILURE);
	if (ac == 1)
	{
		if ((fd = open("a.out", O_RDONLY)) < 0)
		{
			perror("open");
			return(EXIT_FAILURE);
		}
		e->file = ft_strdup("a.out");
	}
	else if (ac == 2)
	{
		if ((fd = open(av[1], O_RDONLY)) < 0)
		{
			perror("open");
			return(EXIT_FAILURE);
		}
		e->file = ft_strdup(av[1]);
	}
	else
	{
		ft_printf("Usage :\n"); //todo
		return (EXIT_FAILURE);
	}
	return (process_file(fd, e));
}
