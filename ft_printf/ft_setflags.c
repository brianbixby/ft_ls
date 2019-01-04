/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setflags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 13:46:17 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/04 13:46:20 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void						ft_initializeprintstruct(t_print *print)
{
	int						i;

	i = -1;
	while (++i < 5)
		print->flag[i] = 0;
	print->minw = 0;
	print->prec = -1;
	print->len = 0;
	print->type = 0;
	print->len_with_no_sign = 0;
	print->neg = 0;
	print->prepend = 0;
	print->prepend_val = 0;
}

void						ft_setflag(const char *s, t_print *print, int *idx)
{
	while (s[*idx] && (s[*idx] == '-' || s[*idx] == '0' || s[*idx] == '+' ||
			s[*idx] == '#' || s[*idx] == ' '))
	{
		if (s[*idx] == '-')
			print->flag[0] = 1;
		else if (s[*idx] == '0')
			print->flag[1] = 1;
		else if (s[*idx] == '+')
			print->flag[2] = 1;
		else if (s[*idx] == '#')
			print->flag[3] = 1;
		else if (s[*idx] == ' ')
			print->flag[4] = 1;
		*idx += 1;
	}
}

void						ft_setminw(const char *s, t_print *print, int *idx,
										va_list ap)
{
	if (print->flag[2] || print->flag[4])
	{
		print->prepend_val = (print->flag[2] ? "+" : " ");
		print->prepend = 1;
	}
	if (s[*idx] == '*')
	{
		print->minw = va_arg(ap, int);
		*idx += 1;
	}
	else if (s[*idx] >= '0' && s[*idx] <= '9')
	{
		print->minw = ft_atoi(&s[*idx]);
		while (s[*idx] >= '0' && s[*idx] <= '9')
			*idx += 1;
	}
}

void						ft_setprec(const char *s, t_print *print, int *idx,
										va_list ap)
{
	if (s[*idx] == '.')
	{
		*idx += 1;
		if (s[*idx] == '*')
		{
			print->prec = va_arg(ap, int);
			*idx += 1;
		}
		else if (s[*idx] >= '0' && s[*idx] <= '9')
		{
			print->prec = ft_atoi(&s[*idx]);
			while (s[*idx] >= '0' && s[*idx] <= '9')
				*idx += 1;
		}
		else
			print->prec = 0;
	}
}

void						ft_setlen(const char *s, t_print *print, int *idx)
{
	if (s[*idx] == 'h' && (s[*idx + 1] && s[*idx + 1] == 'h'))
		print->len = 1;
	else if (s[*idx] == 'h')
		print->len = 2;
	else if (s[*idx] == 'l' && (s[*idx + 1] && s[*idx + 1] == 'l'))
		print->len = 3;
	else if (s[*idx] == 'l')
		print->len = 4;
	else if (s[*idx] == 'j')
		print->len = 5;
	else if (s[*idx] == 'z')
		print->len = 6;
	else if (s[*idx] == 'L')
		print->len = 7;
	if (print->len == 3 || print->len == 1)
		*idx += 2;
	else if (print->len > 0)
		*idx += 1;
}
