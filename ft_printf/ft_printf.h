/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 06:48:45 by bbixby            #+#    #+#             */
/*   Updated: 2018/11/10 06:48:46 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <locale.h>
# include <stdio.h>
# include <stdint.h>

typedef struct		s_print
{
	int				flag[5];
	int				minw;
	int				prec;
	int				len;
	char			type;
	int				len_with_no_sign;
	int				neg;
	int				prepend;
	char			*prepend_val;
}					t_print;

/*
**	ft_printf.c
*/
void				ft_updateflagvals(t_print *print);
void				ft_format2(va_list ap, t_print *print, int *lenptr);
void				ft_format(va_list ap, t_print *print, int *lenptr);
const char			*ft_setflags(const char *s, va_list ap, int *lenptr);
int					ft_printf(const char *s, ...);

/*
**	ft_toascii.c
*/
char				*ft_lltoa_base(long long value, int base, t_print *print);
char				*ft_ulltoa_base(unsigned long long value, int base,
									t_print *print);

/*
**	ft_setflags.c
*/
void				ft_initializeprintstruct(t_print *print);
void				ft_setflag(const char *s, t_print *print, int *idx);
void				ft_setminw(const char *s, t_print *print, int *idx,
								va_list ap);
void				ft_setprec(const char *s, t_print *print, int *idx,
								va_list ap);
void				ft_setlen(const char *s, t_print *print, int *idx);

/*
**	ft_modifiers.c
*/
long long			ft_int_modifier(va_list ap, t_print *print);
unsigned long long	ft_uint_modifier(va_list ap, t_print *print);
long double			ft_f_modifier(va_list ap, t_print *print);

/*
**	ft_print.c
*/
void				ft_printsinglechar(int i, int *lenptr);
void				ft_printchar(int i, int *lenptr, t_print *print);
void				ft_printstr(char *s, int *lenptr);

/*
**	ft_helpers.c
*/
int					ft_atoi(const char *str);
int					ft_strlen(char *s);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strdup(char *s1);
char				*ft_lltoa(long long value);

/*
**	ft_wchar.c
*/
size_t				ft_wlen(wchar_t w);
size_t				ft_wstrlen(wchar_t *s);
void				ft_putwchar(wchar_t wc);
int					ft_putwstr(va_list ap, int *lenptr);

/*
**	ft_print_s.c
*/
int					ft_print_s(char *s, int *lenptr, t_print *print);

/*
**	ft_print_c.c
*/
void				ft_print_c(char c, int *lenptr, t_print *print);

/*
**	ft_print_unsigned.c
*/
void				ft_print_unsigned(char *s, int *lenptr, t_print *print);

/*
**	ft_print_signed.c
*/
void				ft_print_signed(char *s, int *lenptr, t_print *print);

/*
**	ft_print_p.c
*/
void				ft_print_p(char *s, int *lenptr, t_print *print);
void				ft_print_p_helper(char *s, t_print *print, char *ptr,
										int len);

/*
**	ft_printf.c
*/
void				ft_numlen(long long_ld, t_print *print);
char				*ft_ldtoa(long double ld, t_print *print,
						long long multiplier, long long muted);
long long			powk(int x, unsigned int y);
void				ft_print_f(char *s, int *lenptr, t_print *print);

/*
**	ft_print_helpers.c
*/
int					ft_write(char *str, int *lenptr, int size, char *s);
int					ft_null(int *lenptr);
void				ft_putchar(char c);

#endif
