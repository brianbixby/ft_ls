/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:44:29 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/07 16:44:30 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define REV(rev)	((rev) ? (<) : (>))

void	ft_wordsort(char **tab, int len, int rev)
{
	int		i;
	int		a;
	char	*temp;

	i = -1;
	while (++i + 1 < len)
	{
		a = -1;
		while (++a + 1 < len)
		{
			if (!rev ? ft_strcmp(tab[a], tab[a + 1]) > 0 :
				ft_strcmp(tab[a], tab[a + 1]) < 0)
			{
				temp = tab[a];
				tab[a] = tab[a + 1];
				tab[a + 1] = temp;
			}
		}
	}
}

void	ft_namesort(t_file *foarr, int len, int rev)
{
	int		i;
	int		a;
	t_file	temp;

	i = -1;
	while (++i + 1 < len)
	{
		a = -1;
		while (++a + 1 < len)
		{
			if (!rev ? ft_strcmp(foarr[a].name, foarr[a + 1].name) > 0 :
				ft_strcmp(foarr[a].name, foarr[a + 1].name) < 0)
			{
				temp = foarr[a];
				foarr[a] = foarr[a + 1];
				foarr[a + 1] = temp;
			}
		}
	}
}

void	ft_datesort(t_file *foarr, int len)
{
	int		i;
	int		a;
	t_file	temp;

	i = -1;
	while (++i + 1 < len)
	{
		a = -1;
		while (++a + 1 < len)
		{
			if (foarr[a].time < foarr[a + 1].time ||
				(foarr[a].time == foarr[a + 1].time &&
				foarr[a].nano < foarr[a + 1].nano) ||
				(foarr[a].time == foarr[a + 1].time &&
				foarr[a].nano == foarr[a + 1].nano &&
				ft_strcmp(foarr[a].name, foarr[a + 1].name) > 0))
			{
				temp = foarr[a];
				foarr[a] = foarr[a + 1];
				foarr[a + 1] = temp;
			}
		}
	}
}

void	ft_revdatesort(t_file *foarr, int len)
{
	int		i;
	int		a;
	t_file	temp;

	i = -1;
	while (++i + 1 < len)
	{
		a = -1;
		while (++a + 1 < len)
		{
			if (foarr[a].time > foarr[a + 1].time ||
				(foarr[a].time == foarr[a + 1].time &&
				foarr[a].nano > foarr[a + 1].nano) ||
				(foarr[a].time == foarr[a + 1].time &&
				foarr[a].nano == foarr[a + 1].nano &&
				ft_strcmp(foarr[a].name, foarr[a + 1].name) < 0))
			{
				temp = foarr[a];
				foarr[a] = foarr[a + 1];
				foarr[a + 1] = temp;
			}
		}
	}
}

void	ft_foarrsort(t_file *foarr, int *info, int count)
{
	struct stat		st;
	int				i;

	i = -1;
	if (info[3])
	{
		while (++i < count)
		{
			if (lstat(foarr[i].name, &st) == 0)
			{
				foarr[i].time = st.st_mtime;
				foarr[i].nano = st.st_mtimespec.tv_nsec;
			}
		}
		info[2] ? ft_revdatesort(foarr, count) : ft_datesort(foarr, count);
	}
	else
		info[2] ? ft_namesort(foarr, count, 1) : ft_namesort(foarr, count, 0);
}
