/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 15:19:06 by bbixby            #+#    #+#             */
/*   Updated: 2018/11/10 15:19:08 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define ABS(i)  ((i < 0) ? (-i) : (i))

int			ft_atoi(const char *str)
{
	int	ret;
	int	sign;

	ret = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		ret = ret * 10 + *str - 48;
		str++;
	}
	return (ret * sign);
}

int			ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int			ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] == s2[i])
	{
		if (!s1[i])
			return (0);
		i++;
	}
	return (s1[i] - s2[i]);
}

char		*ft_strdup(char *s1)
{
	size_t	i;
	char	*ptr;

	i = ft_strlen(s1);
	if (!(ptr = (char *)malloc(sizeof(*ptr) * (i + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char		*ft_lltoa(long long value)
{
	int					flag;
	int					size;
	char				*tab;
	long long			tmp;
	char				*str;

	flag = (value < 0 ? 1 : 0);
	size = 1 + flag;
	tab = "0123456789abcdef";
	tmp = value;
	while (tmp /= 10)
		size++;
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	str[size] = '\0';
	while (size-- > flag)
	{
		str[size] = tab[ABS(value % 10)];
		value /= 10;
	}
	if (flag)
		str[0] = '-';
	return (str);
}
