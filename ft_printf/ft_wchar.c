/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 21:57:31 by bbixby            #+#    #+#             */
/*   Updated: 2018/11/10 21:57:38 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Largest a single width wide char can be 0x007F
**	Largest a double width wide char can be 0x07FF
**	Largest a triple width wide char can be 0xFFFF
**	Largest a quad width wide char can be 0x10FFFF
**	For 1 byte UTF the mask looks like 0xxxxxxx
**	For 2 byte UTF the mask looks like 110xxxxx for 1st byte then 10xxxxxx
**	for all subsequent bytes
**	For 3 byte UTF the mask looks like 1110xxxx for 1st byte then 10xxxxxx
**	for all subsequent bytes
**	For 4 byte UTF the mask looks like 11110xxx for 1st byte then 10xxxxxx
**	for all subsequent bytes
**
**	For stuff <= 0x7F (01111111) we can just directly write it out.
**
**	For stuff <= 0x07FF (011111111111) we bit shift right by 6 to get the left-
**	most 5 1's (11111) and we 'OR' it with (110xxxxx) == (0xC0). We then take
**	the remaining 6 1's (111111) using (0x3F) == (111111) as a mask and
**	'OR' it with (0x80) == (10000000).
**
**	We continue in a similar manner but use the appropriate mask for the first
**	byte (i.e. 0, 0xC0, 0xE0, 0xF0).
** ref: https://github.com/nmei-42/42-printf/blob/master/printf_utf_utils.c
*/

size_t	ft_wlen(wchar_t w)
{
	if (w < 0x007F)
		return (1);
	else if (w < 0x07FF)
		return (2);
	else if (w < 0xFFFF)
		return (3);
	else if (w < 0x10FFFF)
		return (4);
	return (0);
}

size_t	ft_wstrlen(wchar_t *s)
{
	size_t	len;

	len = 0;
	while (*s != L'\0')
	{
		len += ft_wlen(*s);
		s++;
	}
	return (len);
}

void	ft_putwchar(wchar_t wc)
{
	if (wc <= 0x007F)
		ft_putchar(wc);
	else if (wc <= 0x07FF)
	{
		ft_putchar((wc >> 6) | 0xC0);
		ft_putchar((wc & 0x3F) | 0x80);
	}
	else if (wc <= 0xFFFF)
	{
		ft_putchar((wc >> 12) | 0xE0);
		ft_putchar(((wc >> 6) & 0x3F) | 0x80);
		ft_putchar((wc & 0x3F) | 0x80);
	}
	else if (wc <= 0x10FFFF)
	{
		ft_putchar((wc >> 18) | 0xF0);
		ft_putchar(((wc >> 12) & 0x3F) | 0x80);
		ft_putchar(((wc >> 6) & 0x3F) | 0x80);
		ft_putchar((wc & 0x3F) | 0x80);
	}
}

int		ft_putwstr(va_list ap, int *lenptr)
{
	wchar_t *wstr;
	size_t	wlen;
	size_t	i;

	wstr = va_arg(ap, wchar_t *);
	if (!wstr)
		return (ft_null(lenptr));
	wlen = ft_wstrlen(wstr);
	i = 0;
	while (*wstr && i < wlen)
	{
		if (*wstr <= 0x7F)
			i++;
		else if (*wstr <= 0x7FF)
			i += 2;
		else if (*wstr <= 0xFFFF)
			i += 3;
		else if (*wstr <= 0x10FFFF)
			i += 4;
		if (i <= wlen)
			ft_putwchar(*wstr++);
	}
	*lenptr += (int)i;
	return (0);
}
