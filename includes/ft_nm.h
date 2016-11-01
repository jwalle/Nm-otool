/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/12 13:44:08 by jwalle            #+#    #+#             */
/*   Updated: 2016/10/29 18:47:29 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <unistd.h>
# include <stdlib.h>
# include <pwd.h>
# include <fcntl.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>		//PRINTF A RETIRER
# include "libft.h"
# include "ft_printf.h"

#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <mach-o/ranlib.h>

#define DEBUG printf("File : %s, Function : %s, Line : %d\n", __FILE__,__FUNCTION__,__LINE__)

#define MH_RANLIB 0x72613c21

typedef	struct		s_list64
{
	uint32_t		value;
	char			*name;
	char			type;
	int				n_sect;
	char			n_type;
}					t_list64;


typedef	struct		s_nm_env
{
	int				text;
	int				cpu;
	int				data;
	int				bss;
	t_list			*lists;
	t_list64		**all;
	int				stocked;
}					t_nm_env;

struct		_cpu_type_names
{
	cpu_type_t		cputype;
	const char		*cpu_name;
};

static struct _cpu_type_names cpu_type_names[] =
{
	{CPU_TYPE_I386, "i386"},
	{CPU_TYPE_X86_64, "x86_64"}
};


// void				handle_64(char *ptr, t_nm_env *e);
void				handle_stuff_library(char *ptr, t_nm_env *e);
void				handle_stuff_64(char *ptr, t_nm_env *e);
void				handle_stuff_32(char *ptr, t_nm_env *e);
t_list64			*stock_symbols(struct nlist_64 *array, char *st, int i, t_nm_env *e);
void				sort_output(t_nm_env *e);
void				stock_output(int nsyms, int symoff, int stroff, char *ptr, t_nm_env *e);
void				print_output(t_nm_env *e);
char				get_type(t_list64 *new, t_nm_env *e);

# endif
