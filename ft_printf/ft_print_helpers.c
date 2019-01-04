/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:49:08 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/03 16:49:10 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_write(char *str, int *lenptr, int size, char *s)
{
	write(1, str, size);
	*lenptr += size;
	free(str);
	if (s)
		free(s);
	return (0);
}

int			ft_null(int *lenptr)
{
	write(1, "(null)", 6);
	*lenptr += 6;
	return (0);
}

void		ft_putchar(char c)
{
	write(1, &c, 1);
}
