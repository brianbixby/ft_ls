/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 00:06:56 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/07 00:06:58 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t		ft_strle(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s + len))
		len++;
	return (len);
}

int			ft_cmp(char *s1, char *s2)
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

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	sstart;

	if (!s)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	i = -1;
	sstart = (size_t)start;
	while (++i < len)
		*(str + i) = *(s + sstart + i);
	*(str + i) = '\0';
	return (str);
}

char		*ft_pcat(char *s1, char *s2)
{
	size_t	len;
	size_t	i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	i = 0;
	if (!(str = (char *)malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	len = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = '/';
	while (s2[len])
	{
		str[i + len] = s2[len];
		len++;
	}
	str[i + len] = '\0';
	return (str);
}
