/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 06:57:47 by bbixby            #+#    #+#             */
/*   Updated: 2018/11/11 06:57:48 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_createstring(char *s, t_print *print, char *ptr, int sl[2])
{
	int			idx;

	idx = -1;
	if (!s)
	{
		while (++idx < sl[0])
			ptr[idx] = (print->flag[1] ? '0' : ' ');
	}
	else if (print->flag[0])
	{
		while (++idx < sl[1] && s[idx])
			ptr[idx] = s[idx];
		while (idx < sl[0])
			ptr[idx++] = ' ';
	}
	else
	{
		while (++idx < sl[0] - sl[1])
			ptr[idx] = (print->flag[1] ? '0' : ' ');
		while (*s && idx < sl[0])
			ptr[idx++] = *s++;
	}
}

/*
**	sl[2] = size_len, sl[0] = size, sl[1] = len
*/

int				ft_print_s(char *s, int *lenptr, t_print *print)
{
	int			sl[2];
	char		*ptr;

	if (!s && print->minw == 0)
		return (ft_null(lenptr));
	sl[1] = (!s ? 0 : ft_strlen(s));
	sl[1] = (print->prec == -1 || print->type == '%' || sl[1] < print->prec ?
			sl[1] : print->prec);
	sl[0] = (sl[1] > print->minw ? sl[1] : print->minw);
	if (!(ptr = (char *)malloc(sizeof(char) * (sl[0] + 1))))
		return (0);
	ptr[sl[0]] = '\0';
	ft_createstring(s, print, ptr, sl);
	return (ft_write(ptr, lenptr, sl[0], NULL));
}
