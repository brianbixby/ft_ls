/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 07:54:25 by bbixby            #+#    #+#             */
/*   Updated: 2018/11/10 07:54:28 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printsinglechar(int i, int *lenptr)
{
	char	c;

	c = (char)i;
	write(1, &c, 1);
	*lenptr += 1;
}

void		ft_printchar(int i, int *lenptr, t_print *print)
{
	char	c;
	t_print	myprint;

	myprint = *print;
	c = (char)i;
	write(1, &c, 1);
	*lenptr += 1;
}

void		ft_printstr(char *s, int *lenptr)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
	*lenptr += i;
}
