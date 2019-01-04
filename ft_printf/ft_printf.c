/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 06:48:34 by bbixby            #+#    #+#             */
/*   Updated: 2018/11/10 06:48:36 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define BASE(c) ((c == 'x' || c == 'X') ? (16) : (8))

void						ft_updateflagvals(t_print *print)
{
	print->flag[2] = 0;
	print->flag[4] = 0;
	print->prepend = 0;
	print->prepend_val = 0;
}

void						ft_format2(va_list ap, t_print *print, int *lenptr)
{
	if (print->type == 'u' || print->type == 'U')
	{
		ft_updateflagvals(print);
		ft_print_unsigned(ft_ulltoa_base(ft_uint_modifier(ap, print), 10,
			print), lenptr, print);
	}
	else if (print->type == 'o' || print->type == 'O' || print->type == 'x' ||
			print->type == 'X')
	{
		ft_updateflagvals(print);
		ft_print_signed(ft_ulltoa_base(ft_uint_modifier(ap, print),
			BASE(print->type), print), lenptr, print);
	}
	else if (print->type == 'f' || print->type == 'F')
	{
		print->prec = (print->prec == -1 ? 7 : print->prec + 1);
		ft_print_f(ft_ldtoa(ft_f_modifier(ap, print), print, 0, 0),
			lenptr, print);
	}
	else
		ft_print_c((int)print->type, lenptr, print);
}

void						ft_format(va_list ap, t_print *print, int *lenptr)
{
	if (print->type == 's')
		ft_print_s(va_arg(ap, char *), lenptr, print);
	else if (print->type == 'S')
		ft_putwstr(ap, lenptr);
	else if (print->type == 'c' || print->type == 'C' || print->type == '%')
		print->type == 'c' || print->type == 'C' ? (ft_print_c(va_arg(ap, int),
			lenptr, print)) : (ft_print_s("%", lenptr, print));
	else if (print->type == 'p')
	{
		print->prepend_val = "0x";
		print->prepend = 2;
		ft_print_p(ft_lltoa_base((long long)va_arg(ap, void *), 16, print),
					lenptr, print);
	}
	else if (print->type == 'd' || print->type == 'i')
		ft_print_signed(ft_lltoa_base(ft_int_modifier(ap, print), 10, print),
			lenptr, print);
	else if (print->type == 'D')
		ft_print_signed(ft_lltoa_base((long)va_arg(ap, long), 10, print),
			lenptr, print);
	else
		ft_format2(ap, print, lenptr);
}

const char					*ft_setflags(const char *s, va_list ap, int *lenptr)
{
	int						idx;
	t_print					print;

	idx = -1;
	ft_initializeprintstruct(&print);
	while (s[++idx])
	{
		ft_setflag(s, &print, &idx);
		ft_setminw(s, &print, &idx, ap);
		ft_setprec(s, &print, &idx, ap);
		ft_setlen(s, &print, &idx);
		print.type = s[idx];
		ft_format(ap, &print, lenptr);
		return (&s[idx + 1]);
	}
	return (&s[idx]);
}

int							ft_printf(const char *s, ...)
{
	va_list					ap;
	int						len;
	int						*lenptr;
	int						idx;

	va_start(ap, s);
	len = 0;
	lenptr = &len;
	idx = -1;
	while (s[++idx])
	{
		if (s[idx] != '%')
			ft_printsinglechar((int)s[idx], lenptr);
		else
		{
			idx++;
			s = ft_setflags(&s[idx], ap, lenptr);
			idx = -1;
		}
	}
	va_end(ap);
	return (len);
}
