/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:20:51 by bbixby            #+#    #+#             */
/*   Updated: 2018/11/16 15:20:52 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_print_c(char c, int *lenptr, t_print *print)
{
	int		size;
	char	*ptr;
	int		idx;

	size = (1 > print->minw ? 1 : print->minw);
	if (!(ptr = (char *)malloc(sizeof(char) * (size + 1))))
		return ;
	ptr[size] = '\0';
	idx = 0;
	if (print->flag[0])
	{
		ptr[idx++] = c;
		while (idx < size)
			ptr[idx++] = ' ';
	}
	else
	{
		while (idx < size - 1)
			ptr[idx++] = (print->flag[1] ? '0' : ' ');
		ptr[idx] = c;
	}
	ft_write(ptr, lenptr, size, NULL);
}
