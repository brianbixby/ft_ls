/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 07:34:52 by bbixby            #+#    #+#             */
/*   Updated: 2018/11/28 07:34:54 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define ABS(i)  ((i < 0) ? (-i) : (i))

void					ft_print_f(char *s, int *lenptr, t_print *print)
{
	int					r;
	int					i;

	i = print->len_with_no_sign + print->neg - 2;
	r = (s[i + 1] - 48 >= 5 ? 1 : 0);
	if (print->prec)
	{
		while (i >= 0 && r)
		{
			if (s[i] == '9')
				s[i] = '0';
			else if (s[i] != '.')
			{
				s[i] += 1;
				r = 0;
			}
			i--;
		}
		if (r)
			write(1, "1", 1);
	}
	write(1, s, print->len_with_no_sign + print->neg - 1);
	*lenptr += (print->len_with_no_sign + print->neg - 1);
}

long long				powk(int x, unsigned int y)
{
	if (y == 0)
		return (1);
	else if (y % 2 == 0)
		return (powk(x, y / 2) * powk(x, y / 2));
	else
		return (x * powk(x, y / 2) * powk(x, y / 2));
}

static void				ft_ldtoahelper(t_print *print, char *str, int *i,
							long double ld)
{
	char				*temp;

	str[print->len_with_no_sign + print->neg] = '\0';
	temp = ft_lltoa((long long)ld);
	while (temp[*i])
	{
		str[*i] = temp[*i];
		*i += 1;
	}
	if (print->prec)
		str[*i] = '.';
}

char					*ft_ldtoa(long double ld, t_print *print,
							long long multiplier, long long muted)
{
	unsigned long long	after_point_ld;
	long				xy;
	char				*str;
	int					i;

	i = 0;
	ft_numlen((long)ld, print);
	if (!(str = (char *)malloc(sizeof(char) *
		(print->len_with_no_sign + print->neg + 1))))
		return (NULL);
	ft_ldtoahelper(print, str, &i, ld);
	after_point_ld = (unsigned long long)ABS(ld * powk(10, print->prec));
	multiplier = powk(10, (print->prec - 1));
	xy = 0;
	while (xy++ < print->prec)
	{
		muted = (after_point_ld / multiplier);
		muted = ABS(muted % 10);
		str[++i] = (char)muted + 48;
		multiplier /= 10;
	}
	return (str);
}

void					ft_numlen(long long_ld, t_print *print)
{
	long				denom;

	print->len_with_no_sign = 1;
	if (long_ld < 0)
		print->neg = 1;
	denom = 10;
	while (long_ld /= denom)
		print->len_with_no_sign++;
	if (print->prec)
		print->len_with_no_sign += (print->prec + 1);
}
