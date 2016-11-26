/* ****************l********************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/12 13:44:08 by jwalle            #+#    #+#             */
/*   Updated: 2016/10/29 18:47:29 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

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
#include <ar.h>

#define DEBUG ft_printf("File : %s, Function : %s, Line : %d\n", __FILE__,__FUNCTION__,__LINE__)

#define MH_RANLIB 0x72613c21

typedef	struct		s_otool_env
{
	int				fat;
	int				dylink;
	int				cpu;
	int				lib;
	int				dylib;
	int				obj;
	int				bundle;
	char			*file;

}					t_otool_env;
/*
struct		_cpu_type_names
{
	cpu_type_t		cputype;
	const char		*cpu_name;
};

static struct _cpu_type_names cpu_type_names[] =
{
	{CPU_TYPE_I386, "i386"},
	{CPU_TYPE_X86_64, "x86_64"}
};*/

void				print_dat_shit(uint32_t size, uint32_t addr, char *offset, t_otool_env *e);
void				handle_otool_library(char *ptr, t_otool_env *e);
void				handle_otool_64(char *ptr, t_otool_env *e);
void				handle_otool_32(char *ptr, t_otool_env *e);
void				handle_otool_fat(char *ptr, t_otool_env *e);
void				handle_otool_taf(char *ptr, t_otool_env *e);
void				ft_otool(char *ptr, t_otool_env *e);

# endif
