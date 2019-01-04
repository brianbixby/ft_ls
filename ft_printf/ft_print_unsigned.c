/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 07:41:46 by bbixby            #+#    #+#             */
/*   Updated: 2018/11/11 07:41:47 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_leftalign(char *s, char *str, int charstoprint, int size)
{
	int		i;

	i = -1;
	while (++i < charstoprint)
		str[i] = s[i];
	while (i < size)
	{
		str[i] = ' ';
		i++;
	}
}

static void		ft_rightalign(char *s, char *str, int charstoprint,
					t_print *print)
{
	int		i;
	int		j;
	int		size;

	i = -1;
	j = 0;
	size = (print->minw > charstoprint ? print->minw : charstoprint);
	while (++i < size - charstoprint)
		str[i] = (print->flag[1] ? '0' : ' ');
	while (i + print->len_with_no_sign < size)
		str[i++] = '0';
	while (i < size)
	{
		str[i] = s[j];
		i++;
		j++;
	}
}

void			ft_print_unsigned(char *s, int *lenptr, t_print *print)
{
	int		i;
	int		charstoprint;
	int		size;
	char	*str;

	i = ft_strlen(s);
	charstoprint = (print->prec == -1 || i > print->prec ? i : print->prec);
	size = (print->minw > charstoprint ? print->minw : charstoprint);
	if (!print->flag[3] && print->prec == 0 && !print->flag[1] &&
		ft_strcmp(s, "0") == 0)
		size = print->minw;
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return ;
	str[size] = '\0';
	i = -1;
	if (!print->flag[3] && print->prec == 0 && !print->flag[1] &&
		ft_strcmp(s, "0") == 0)
		while (++i < size)
			str[i] = ' ';
	else if (print->flag[0])
		ft_leftalign(s, str, charstoprint, size);
	else
		ft_rightalign(s, str, charstoprint, print);
	ft_write(str, lenptr, size, s);
}
