/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/12 13:44:08 by jwalle            #+#    #+#             */
/*   Updated: 2016/10/13 16:35:32 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdlib.h>
# include <pwd.h>
# include <fcntl.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>		//PRINTF A RETIRER
# include "libft.h"
# include "ft_printf.h"

typedef	struct		s_list64
{
	uint32_t		value;
	char			*name;
	char			type;
}					t_list64;


typedef	struct		s_nm_env
{
	int				plop;
	t_list			*lists;
	t_list64		**all;
	int				stocked;
}					t_nm_env;

void				merge_sort(t_list **ref);

# endif
