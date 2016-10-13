/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 17:01:35 by jwalle            #+#    #+#             */
/*   Updated: 2016/06/19 19:54:55 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdint.h>
# include <limits.h>
# include <wchar.h>
# include <stdlib.h>
# include <unistd.h>

# define HEXA "0123456789abcdef"
# define HEXA_MAJ "0123456789ABCDEF"
# define OCTAL "0x000000000000"
# define FLAGS "-+ #0"
# define LENGTH "hljz"
# define SPECIFIER "sSpdDioOuUxXcC%"

typedef	struct	s_flags
{
	int			minus;
	int			plus;
	int			zero;
	int			htag;
	int			space;
}				t_flags;

typedef	struct	s_length
{
	int			no;
	int			l;
	int			ll;
	int			h;
	int			hh;
	int			j;
	int			z;
}				t_length;

typedef	struct	s_arg
{
	t_flags		*flags;
	t_length	*length;
	int			width;
	int			precision;
	int			precision_null;
	char		specifier;
	int			hex;
	int			is_unsigned;
}				t_arg;

typedef	struct	s_env
{
	int			ret;
}				t_env;

int				ft_printf(const char *format,
					...) __attribute__((format(printf,1,2)));
char			*ft_strndup(char *str, int i);
int				parse(const char *format, t_arg *arg, va_list list);
int				parse_two(const char *format, t_arg *arg, int n);
void			ft_atoi_hex(void *ptr);
void			arg_is_int(t_env *e, t_arg *arg, va_list list);
void			arg_is_u(t_env *e, t_arg *arg, va_list list);
void			arg_is_c(t_env *e, t_arg *arg, va_list list);
void			arg_is_string(t_env *e, t_arg *arg, va_list list);
void			arg_is_p(t_env *e, t_arg *arg, va_list list);
void			init_length(t_length *length);
void			init_arg(t_arg *arg);
int				ft_int_octal_len(unsigned long long n);
int				ft_int_hex_len(unsigned long long n);
int				ft_intlen(int n);
int				ft_ll_intlen(unsigned long long n);
int				ft_parse_len(unsigned long long n, char spe);
void			ft_putllnbr(t_env *e, long long int n);
void			parse_number(t_env *e, long long number, char spe);
int				format_output(t_env *e, int len, int signe, t_arg *arg);
int				format_left_width(t_env *e, t_arg *arg, int len, int signe);
int				print_hex(t_env *e, char spe);
void			ft_putnbr_octal(t_env *e, unsigned long long number);
void			ft_putnbr_hexa(t_env *e, unsigned long long number, char spe);
void			ft_putllunbr(t_env *e, unsigned long long int n);
void			ft_putchar_ret(t_env *e, char c);
void			ft_putstr_ret(t_env *e, const char *s);
void			print_char(t_env *e, t_arg *arg, char c);
size_t			ft_strlen_ptf(const char *s);
int				ft_atoi_ptf(const char *str);
void			ft_bzero_ptf(void *s, size_t n);
int				ft_isdigit_ptf(int c);
void			ft_putstr_ptf(const char *s);
char			*ft_strchr_ptf(const char *s, int c);
int				ft_strcmp_ptf(const char *s1, const char *s2);
char			*ft_strncpy_ptf(char *dest, const char *src, size_t n);
char			*ft_strnew_ptf(size_t size);
void			arg_is_wchar(t_env *e, wchar_t w);
void			print_wstr(t_env *e, wchar_t *w_str, t_arg *arg);
void			arg_is_wstr(t_env *e, wchar_t *w_str);
int				get_wchar_len(wchar_t c);
int				format_hex(t_arg *arg, t_env *e, int signe);
void			destroy_mem(t_arg *arg, t_env *e);
void			init_mem(t_env *e, t_arg *arg);
int				process_color(t_env *e, const char *format);

#endif
