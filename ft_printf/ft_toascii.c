/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 15:27:10 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/04 15:27:12 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define BASE(c) ((c == 'x' || c == 'X') ? (16) : (8))
#define ABS(i)  ((i < 0) ? (-i) : (i))

static void					ft_isneg(t_print *print)
{
	print->neg = 1;
	print->prepend_val = "-";
	print->prepend = 1;
}

static char					*ft_ismaxmin(t_print *print)
{
	print->len_with_no_sign = 19;
	return (ft_strdup("9223372036854775808"));
}

char						*ft_lltoa_base(long long value, int base,
											t_print *print)
{
	int						size;
	char					*tab;
	long long				tmp;
	char					*str;

	size = 1;
	tab = (print->type == 'X' ? ("0123456789ABCDEF") : ("0123456789abcdef"));
	tmp = value;
	while (tmp /= base)
		size++;
	if (value < 0)
		ft_isneg(print);
	if (value == INTMAX_MIN)
		return (ft_ismaxmin(print));
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	str[size] = '\0';
	while (size-- > 0)
	{
		str[size] = tab[ABS(value % base)];
		value /= base;
	}
	print->len_with_no_sign = ft_strlen(str);
	return (str);
}

static void					ft_setprependval(t_print *print)
{
	if (print->type == 'o' || print->type == 'O')
	{
		print->prepend_val = "0";
		print->prepend = 1;
	}
	else
	{
		print->prepend_val = (print->type == 'x' ? "0x" : "0X");
		print->prepend = 2;
	}
}

char						*ft_ulltoa_base(unsigned long long value, int base,
											t_print *print)
{
	unsigned long long		size;
	char					*tab;
	unsigned long long		tmp;
	char					*str;

	size = 1;
	tab = (print->type == 'X' ? ("0123456789ABCDEF") : ("0123456789abcdef"));
	tmp = value;
	while (tmp /= base)
		size++;
	if (!(str = (char *)malloc(sizeof(char) * (size + tmp + 1))))
		return (NULL);
	str[size] = '\0';
	if (print->flag[3] && (print->type == 'o' || print->type == 'x' ||
		print->type == 'X' || print->type == 'O') && value != 0)
		ft_setprependval(print);
	while (size-- > tmp)
	{
		str[size] = tab[ABS(value % base)];
		value /= base;
	}
	print->len_with_no_sign = ft_strlen(str);
	return (str);
}
