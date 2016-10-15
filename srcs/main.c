/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 16:10:23 by jwalle            #+#    #+#             */
/*   Updated: 2016/10/14 16:53:10 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

/*
void	print_symbol(int type)
{

}*/

// void	sort_array(void *array, int nsyms, char *st)
void	sort_array(struct nlist_64 *array, int nsyms, char *st)
{
	int				x;
	int				y;
	// void			*swap;
	struct nlist_64 *swap;

	x = 1;
	swap = malloc(sizeof(struct nlist_64));
	while (x < (nsyms - 1))
	{		
		y = 0;
		while (y < 10)
		{
			printf("plop\n");
			printf("%c --> %c\n", (st + array[x].n_un.n_strx)[y] ,(st + array[x + 1].n_un.n_strx)[y]);
			printf("plop\n");
			// if ((st + (struct nlist_64*)array[x].n_un.n_strx + y) > (st + (struct nlist_64*)array[x + 1].n_un.n_strx + y))
			if ((st + array[x].n_un.n_strx)[y] > (st + array[x + 1].n_un.n_strx)[y])
			{
				printf("%c --> %c\n", (st + array[x].n_un.n_strx)[y] ,(st + array[x + 1].n_un.n_strx)[y]);
				printf("PPLLPOPO\n");
				// swap = &array[x];
				// array[x] = array[x + 1];
				// array[x + 1] = *swap;
				ft_memcpy(swap , &array[x], sizeof(struct nlist_64));
				printf("UN\n");
				ft_memcpy(&array[x] ,&array[x + 1], sizeof(struct nlist_64));
				printf("deux\n");
				ft_memcpy(&array[x + 1] ,&swap, sizeof(struct nlist_64));
				printf("trois\n");
			}
			y++;
		}
		x++;
	}
}



void	print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int				i;
	char			*string_table;
	struct nlist_64	*array;

	array = (void *)ptr + symoff;
	string_table = (void *)ptr + stroff;
	//sort_array(array, nsyms, string_table);
	for (i = 0; i < nsyms; ++i)
	{
		if (array[i].n_type == 15)
			printf("%016llx T %s\n", array[i].n_value, string_table + array[i].n_un.n_strx);
		else if (array[i].n_type == 14)
			printf("%016llx t %s\n", array[i].n_value, string_table + array[i].n_un.n_strx);
		else if (array[i].n_type == N_EXT)
			printf("%16.x U %s\n", 0, string_table + array[i].n_un.n_strx);
		else
			printf("%016llx %hhu %s\n", array[i].n_value, array[i].n_type, string_table + array[i].n_un.n_strx);
	}
}

/*struct mach_header_64 {
**	uint32_t	magic;		 	-->mach magic number identifier
**	cpu_type_t	cputype;		--> cpu specifier
**	cpu_subtype_t	cpusubtype;	--> machine specifier
**	uint32_t	filetype;		--> type of file
**	uint32_t	ncmds;			--> number of load commands
**	uint32_t	sizeofcmds;		--> the size of all the load commands
**	uint32_t	flags;			--> flags 
**	uint32_t	reserved;		--> reserved 
**};
*/

/*
**struct load_command {
**	uint32_t cmd;		--> type of load command
**	uint32_t cmdsize;	--> total size of command in bytes
**};
*/

/*
 * The symtab_command contains the offsets and sizes of the link-edit 4.3BSD
 * "stab" style symbol table information as described in the header files
 * <nlist.h> and <stab.h>.
**
**
**struct symtab_command {
**	uint32_t	cmd;		--> LC_SYMTAB
**	uint32_t	cmdsize;	--> sizeof(struct symtab_command)
**	uint32_t	symoff;		--> symbol table offset
**	uint32_t	nsyms;		--> number of symbol table entries
**	uint32_t	stroff;		--> string table offset
**	uint32_t	strsize;	--> string table size in bytes
**};
*/

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
	for (i = 0 ; ncmds > i ; ++i)
	{
	//	printf("PLOOOOOOOOOOOOOOOP <------------\n");
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
		//	printf("symtab command : nsyms = %d, symoff = %d, stroff = %d\n" , sym->nsyms, sym->symoff, sym->stroff);
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
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
	else if (magic_number == MH_MAGIC)
	{
		puts("c'est du 32 !!");
	}
}

int		main(int ac, char **av)
{
	int 		fd;
	char		*ptr;
	struct stat	buf;

	fd = 0;
	
	if (ac != 2)
	{
		ft_printf("Please give me argument :(.\n");
		return (EXIT_FAILURE);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		perror("open");
		return(EXIT_FAILURE);
	}
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
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
