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
	char	c;
	char	mask;
	char	ret;

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
		ret = 't';
	if ((c & N_EXT) && ret != '?')
		ret = ft_toupper(ret);
	// else
		// ret = ft_tolower(ret);
	//	if (array[i].n_type == 1)
	//	return ('U');
	printf("PLop = %c\n", ret);
	return (ret);
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


void	sort_output(t_nm_env *e)
{
	int	i;
	int n;
	t_list64 *temp;

	i = 0;
	n = e->stocked;
	while (i < n - 1)
	{
		if (ft_strcmp(e->all[i]->name, e->all[i + 1]->name) < 1)
		{
			temp = e->all[i];
			e->all[i] = e->all[i + 1];
			e->all[i + 1] = temp;
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
			all[j] = stock_symbols(array, string_table, i);
			j++;
			printf("plop = %s, %i, %i, %i, %i, (%d)\n", string_table + array[i].n_un.n_strx, array[i].n_type & N_STAB
																	 , array[i].n_type & N_PEXT
																	 , array[i].n_type & N_TYPE
																	 , array[i].n_type & N_EXT
																	 , array[i].n_un.n_strx);
		
		}
		i++;
	}
	e->stocked = j;
	printf("%i, %i, %i, %i, %i\n", 0x0, 0x2, 0xe, 0xc, 0xa);
}

void	print_output(t_nm_env *e)
{
	int				i;

	i = 0;
	while(i < e->stocked)
	{
		if (e->all[i]->type == 'U')
			printf("%16.x %c %s\n", 0, e->all[i]->type, e->all[i]->name);
		else if (e->all[i]->type == '?')
			printf("%016x %c %s\n", 0, e->all[i]->type, e->all[i]->name);
		else if (e->all[i]->type == 'T')
			printf("%016x %c %s\n", e->all[i]->value, e->all[i]->type, e->all[i]->name);
		else
			printf("%016x %c %s <------------\n", e->all[i]->value, e->all[i]->type, e->all[i]->name);
		i++;
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
			sort_output(e);
			//merge_sort(&e->lists);
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
