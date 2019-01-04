/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modifiers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:00:34 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/03 17:00:36 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** promoting to int instead of char and unsigned char
** because va_arg automatically promotes it to an int
*/

long long					ft_int_modifier(va_list ap, t_print *print)
{
	long long				ret;

	ret = 0;
	if (print->len == 1)
		ret = (signed char)va_arg(ap, int);
	else if (print->len == 2)
		ret = (short)va_arg(ap, int);
	else if (print->len == 3)
		ret = (long long)va_arg(ap, long long);
	else if (print->len == 4)
		ret = (long)va_arg(ap, long);
	else if (print->len == 5)
		ret = (long long)va_arg(ap, long long);
	else if (print->len == 6)
		ret = (ssize_t)va_arg(ap, ssize_t);
	else if (print->len == 7)
		ret = (long double)va_arg(ap, long double);
	else
		ret = va_arg(ap, int);
	return (ret);
}

unsigned long long			ft_uint_modifier(va_list ap, t_print *print)
{
	unsigned long long		ret;

	ret = 0;
	if (print->type == 'O' || print->type == 'U')
		ret = va_arg(ap, unsigned long);
	else if (print->len == 1)
		ret = (unsigned char)va_arg(ap, unsigned int);
	else if (print->len == 2)
		ret = (print->type == 'U' ? va_arg(ap, unsigned long) :
		(unsigned short)va_arg(ap, unsigned int));
	else if (print->len == 3)
		ret = (unsigned long long)va_arg(ap, unsigned long long);
	else if (print->len == 4)
		ret = (unsigned long)va_arg(ap, unsigned long);
	else if (print->len == 5)
		ret = (unsigned long long)va_arg(ap, unsigned long long);
	else if (print->len == 6)
		ret = (size_t)va_arg(ap, size_t);
	else
		ret = (print->type == 'U' ? va_arg(ap, unsigned long) :
			va_arg(ap, unsigned int));
	return (ret);
}

long double					ft_f_modifier(va_list ap, t_print *print)
{
	long double				ret;

	ret = 0;
	if (print->len == 4)
		ret = (double)va_arg(ap, double);
	else if (print->len == 7)
		ret = (long double)va_arg(ap, long double);
	else
		ret = (long double)va_arg(ap, double);
	return (ret);
}
