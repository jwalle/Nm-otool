/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 16:10:23 by jwalle            #+#    #+#             */
/*   Updated: 2016/10/13 17:11:37 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

void	handle_64(char *ptr)
{
	int						i;
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	
	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	for (i = 0 ; ncmds < i ; ++i)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

void	nm(char *ptr)
{
	unsigned int magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
	{
		puts("c'est du 64 !!");
		handle_64(ptr);
	}
}

int		main(int ac, char **av)
{
	int 		fd;
	char		*ptr;
	struct stat	buf;

	fd = 0;
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
	}
	if ((fstat(fd, &buf)) < 0)
		return (0);
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		perror("mmap");
		return (EXIT_FAILURE);
	}
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (0);
}
