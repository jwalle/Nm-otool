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

char		get_type(struct nlist_64 *array, int i)
{
	if (array[i].n_type == 1)
		return ('U');
	else if (array[i].n_type == 15)
		return ('T');
	//	if (array[i].n_type == 1)
	//	return ('U');
	else
		return ('?');
}

t_list64	*stock_symbols(struct nlist_64 *array, char *st, int i)
{
	t_list64	*new;

	if (!(new = malloc(sizeof(t_list64))))
		return (NULL);
	new->value = array[i].n_value;

	//printf("plop = %s\n", st + array[i].n_un.n_strx);

	new->name = ft_strdup(st + array[i].n_un.n_strx);
	new->type = get_type(array, i);
	return (new);	
}

void	stock_output(int nsyms, int symoff, int stroff, char *ptr, t_nm_env *e)
{
	int				i;
	char			*string_table;
	struct nlist_64	*array;

	i = 0;
	array = (void *)ptr + symoff;
	string_table = (void *)ptr + stroff;
	while (i < nsyms)
	{
		printf("plop = %s\n", string_table + array[i].n_un.n_strx);
		e->lists = ft_lst_push(e->lists, stock_symbols(array, string_table, i));
		i++;
	}
}

void	print_output(t_nm_env *e)
{
	t_list			*list;
	t_list64		*current;

	list = e->lists;
	while(list)
	{
		current = (t_list64*)list->data;
		if (current->type == 'U')
			printf("%16.x %c %s\n", 0, current->type, current->name);
		/*else if (current->type == '?')
			printf("%016x %c %s\n", 0, current->type, current->name);
		else if (current->type == 'T')
			printf("%016x %c %s\n", 0, current->type, current->name);*/
		else
			printf("%016x %c %s <------------\n", current->value, current->type, current->name);
		list = list->next;
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

void	handle_64(char *ptr, t_nm_env *e)
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
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			printf("symtab command : nsyms = %d, symoff = %d, stroff = %d\n" , sym->nsyms, sym->symoff, sym->stroff);
			stock_output(sym->nsyms, sym->symoff, sym->stroff, ptr, e);
			merge_sort(&e->lists);
			print_output(e);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

void	nm(char *ptr, t_nm_env *e)
{
	unsigned int magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
	{
		puts("c'est du 64 !!");
		handle_64(ptr, e);
	}
	else if (magic_number == MH_MAGIC)
	{
		puts("c'est du 32 !!");
	}
}

int		main(int ac, char **av)
{
	int 			fd;
	char			*ptr;
	struct stat		buf;
	t_nm_env		*e;

	fd = 0;
	e = (t_nm_env *)malloc(sizeof(t_nm_env));
	e->lists = NULL;
		// return (EXIT_FAILURE);
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
	nm(ptr, e);
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
