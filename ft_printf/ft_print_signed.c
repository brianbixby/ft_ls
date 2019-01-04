/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_signed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 05:44:20 by bbixby            #+#    #+#             */
/*   Updated: 2018/11/17 05:44:26 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_leftalign(t_print *print, char *ptr, char *s, int size)
{
	int			pidx;
	int			sidx;

	pidx = -1;
	sidx = -1;
	if (print->neg)
		ptr[++pidx] = '-';
	else if (print->flag[2] || print->flag[4])
		ptr[++pidx] = (print->flag[2] ? '+' : ' ');
	if (print->type == 'x' || print->type == 'X' || print->type == 'o'
		|| print->type == 'O')
		while (print->prepend--)
			ptr[++pidx] = *(print->prepend_val++);
	while (--print->prec - print->len_with_no_sign >= 0)
		ptr[++pidx] = '0';
	while (s[++sidx])
		ptr[++pidx] = s[sidx];
	while (++pidx < size)
		ptr[pidx] = ' ';
}

static void		ft_rightalign2(t_print *print, char *ptr, char *s, int size)
{
	int			pidx;
	int			sidx;

	pidx = -1;
	sidx = -1;
	if (print->prec > print->len_with_no_sign)
	{
		while (pidx + 1 + print->prepend + print->prec < size)
			ptr[++pidx] = ' ';
		while (print->prepend--)
			ptr[++pidx] = *(print->prepend_val++);
		while (pidx + 1 + print->len_with_no_sign < size)
			ptr[++pidx] = '0';
		while (++pidx < size)
			ptr[pidx] = s[++sidx];
	}
}

static void		ft_rightalign(t_print *print, char *ptr, char *s, int size)
{
	int			pidx;
	int			sidx;

	pidx = -1;
	sidx = -1;
	if (print->flag[1] && print->prec == -1)
	{
		while (print->prepend--)
			ptr[++pidx] = *(print->prepend_val++);
		while (pidx + print->len_with_no_sign + 1 < size)
			ptr[++pidx] = '0';
		while (s[++sidx])
			ptr[++pidx] = s[sidx];
	}
	else if (print->prec <= print->len_with_no_sign)
	{
		while (pidx + 1 + print->prepend + print->len_with_no_sign < size)
			ptr[++pidx] = ' ';
		while (print->prepend--)
			ptr[++pidx] = *(print->prepend_val++);
		while (++pidx < size)
			ptr[pidx] = s[++sidx];
	}
	else
		ft_rightalign2(print, ptr, s, size);
}

static void		ft_print_signed_helper(t_print *print)
{
	(print->prec == 0 && print->type == 'x') && (print->len_with_no_sign = 0);
	if ((print->type == 'o' || print->type == 'O') && print->prec >
		print->len_with_no_sign + print->prepend && print->prec > print->minw)
		print->prec -= print->prepend;
}

void			ft_print_signed(char *s, int *lenptr, t_print *print)
{
	int			size;
	char		*ptr;
	int			idx;

	ft_print_signed_helper(print);
	size = (print->len_with_no_sign + print->prepend > print->minw ?
		print->len_with_no_sign + print->prepend : print->minw);
	if (print->prec + print->prepend > size)
		size = print->prec + print->prepend;
	if (!print->flag[3] && print->prec == 0 && !print->flag[1] &&
		ft_strcmp(s, "0") == 0)
		size = print->minw;
	if (!(ptr = (char *)malloc(sizeof(char) * (size + 1))))
		return ;
	ptr[size] = '\0';
	idx = -1;
	if (!print->flag[3] && print->prec == 0 && !print->flag[1] &&
		ft_strcmp(s, "0") == 0)
		while (++idx < size)
			ptr[idx] = ' ';
	else if (print->flag[0])
		ft_leftalign(print, ptr, s, size);
	else
		ft_rightalign(print, ptr, s, size);
	ft_write(ptr, lenptr, size, s);
}
