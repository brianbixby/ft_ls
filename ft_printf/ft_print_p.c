/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:27:24 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/03 15:27:43 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_p_helper2(char *s, t_print *print, char *ptr, int len)
{
	int		idx;
	int		size;

	idx = -1;
	size = (len > print->minw ? len : print->minw);
	if (print->flag[1])
	{
		while (print->prepend--)
			ptr[++idx] = *(print->prepend_val++);
		while (idx <= size - len)
			ptr[++idx] = '0';
	}
	else
	{
		while (idx + 1 < size - len)
			ptr[++idx] = (print->flag[1] ? '0' : ' ');
		while (print->prepend--)
			ptr[++idx] = *(print->prepend_val++);
	}
	if (print->prec > ft_strlen(s))
		while (idx + 1 < size - ft_strlen(s))
			ptr[++idx] = '0';
	while (*s && idx + 1 < size)
		ptr[++idx] = *s++;
}

void		ft_print_p_helper(char *s, t_print *print, char *ptr, int len)
{
	int		idx;
	int		size;

	idx = -1;
	size = (len > print->minw ? len : print->minw);
	if (print->flag[0])
	{
		while (print->prepend--)
			ptr[++idx] = *(print->prepend_val++);
		while (idx < len && *s)
			ptr[++idx] = *s++;
		while (idx++ < size)
			ptr[idx] = ' ';
		return ;
	}
	ft_print_p_helper2(s, print, ptr, len);
}

void		ft_print_p(char *s, int *lenptr, t_print *print)
{
	int		len;
	int		size;
	char	*ptr;

	if (!s)
	{
		write(1, "(null)", 6);
		*lenptr += 6;
		return ;
	}
	len = (print->prec == -1 || print->prec < ft_strlen(s) ?
			ft_strlen(s) + print->prepend : print->prec + print->prepend);
	if (print->prec == 0)
		len -= ft_strlen(s);
	size = (len > print->minw ? len : print->minw);
	if (!(ptr = (char *)malloc(sizeof(char) * (size + 1))))
		return ;
	ptr[size] = '\0';
	ft_print_p_helper(s, print, ptr, len);
	ft_write(ptr, lenptr, size, s);
}
