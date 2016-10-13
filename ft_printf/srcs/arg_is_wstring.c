/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_is_wstring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 20:20:42 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/19 20:34:51 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_wstrlen_ptf(wchar_t *w)
{
	int	i;
	int ret;

	i = 0;
	ret = 0;
	while (w[i])
		ret += get_wchar_len(w[i++]);
	return (ret);
}

void	arg_is_wstr(t_env *e, wchar_t *w_str)
{
	int i;

	i = 0;
	while (w_str[i])
	{
		arg_is_wchar(e, w_str[i++]);
	}
}

int		wstr_precision(wchar_t *w_str, t_arg *arg, t_env *e)
{
	int i;
	int temp;

	i = 0;
	temp = 0;
	if (w_str && !arg->precision_null)
	{
		if (arg->precision && (arg->precision < ft_wstrlen_ptf(w_str)))
		{
			while (w_str[i] && arg->precision >= temp + get_wchar_len(w_str[i]))
			{
				arg_is_wchar(e, w_str[i]);
				temp += get_wchar_len(w_str[i]);
				i++;
			}
		}
		else
			arg_is_wstr(e, w_str);
	}
	else if (!w_str && !arg->precision_null)
		ft_putstr_ret(e, "(null)");
	return (temp);
}

void	print_wstr(t_env *e, wchar_t *w_str, t_arg *arg)
{
	int		len;
	int		temp;
	int		i;

	temp = 0;
	i = 0;
	w_str ? len = ft_wstrlen_ptf(w_str) : 6;
	if ((arg->precision && (arg->precision < len)) || arg->precision_null)
	{
		len = 0;
		while (len + get_wchar_len(w_str[i]) <= arg->precision)
			len += get_wchar_len(w_str[i++]);
	}
	i = 0;
	while (!arg->flags->minus && ((arg->width - temp) > len))
	{
		arg->flags->zero ? ft_putchar_ret(e, '0') : ft_putchar_ret(e, ' ');
		temp++;
	}
	temp = wstr_precision(w_str, arg, e);
	while (arg->flags->minus && (arg->width > (len + temp++)))
		ft_putchar_ret(e, ' ');
}
