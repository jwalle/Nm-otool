/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 19:13:09 by jwalle            #+#    #+#             */
/*   Updated: 2016/10/29 19:13:12 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**struct mach_header_64 {
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
** The symtab_command contains the offsets and sizes of the link-edit 4.3BSD
** "stab" style symbol table information as described in the header files
** <nlist.h> and <stab.h>.
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
