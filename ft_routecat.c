/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routecat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 01:33:27 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/18 01:33:30 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ft_routecat(char *s1, char *s2)
{
	size_t	len;
	int		i;
	char	*ptr;
	int		flag;

	if (ft_strcmp(s1, ".") == 0)
		return (ft_routecat2(s2));
	if (ft_strle(s1) < 2 || (s1[0] != '.' || s1[1] != '/'))
		return (ft_routecat3(s1, s2));
	flag = (*s1 == '.' ? 0 : 1);
	len = ft_strle(s1) + ft_strle(s2) + 2;
	i = -1;
	if (!(ptr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (flag)
		ptr[0] = '/';
	if (*s1 == '/')
		s1++;
	while (s1[++i])
		ptr[i + flag] = s1[i];
	ptr[flag + i++] = '/';
	while (*s2)
		ptr[flag + i++] = *s2++;
	ptr[flag + i] = '\0';
	return (ptr);
}

char		*ft_routecat2(char *s1)
{
	size_t	len;
	int		i;
	char	*ptr;

	len = ft_strle(s1) + 2;
	i = -1;
	if (!(ptr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ptr[0] = '.';
	ptr[1] = '/';
	if (*s1 == '/')
		s1++;
	while (s1[++i])
		ptr[i + 2] = s1[i];
	ptr[2 + i] = '\0';
	return (ptr);
}

char		*ft_routecat3(char *s1, char *s2)
{
	size_t	len;
	int		i;
	char	*ptr;

	len = ft_strle(s1) + ft_strle(s2) + 3;
	i = -1;
	if (!(ptr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ptr[0] = '.';
	ptr[1] = '/';
	if (*s1 == '/')
		s1++;
	while (s1[++i])
		ptr[i + 2] = s1[i];
	ptr[2 + i++] = '/';
	while (*s2)
		ptr[2 + i++] = *s2++;
	ptr[2 + i] = '\0';
	return (ptr);
}
