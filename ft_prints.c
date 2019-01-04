/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:42:43 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/07 16:42:54 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_printpermden(char *folder, t_queue **foqueue)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (folder[++i])
	{
		if (folder[i] == '/')
			j = i + 1;
	}
	foqueue = &(*foqueue)->next;
	ft_printf("%s%s%s\n", "ls: ", &folder[j], ": Permission denied");
	if ((*foqueue))
		ft_printf("\n");
	return (0);
}

int			*ft_printnomatches(char *av, int *info, char option)
{
	char	*str;
	int		i;

	str = "-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1*";
	i = 0;
	while (str[i] && str[i] != option)
		i++;
	if (i == 39)
		ft_printf("%s%c\n%s\n", "ls: illegal option -- ", option,
		"usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]");
	else
		ft_printf("%s%s\n", "zsh: no matches found: ", av);
	info[0] = -1;
	return (info);
}

void		ft_printerrors(t_queue *equeue)
{
	t_queue	*temp;

	temp = NULL;
	ft_list_sort(&equeue, 0);
	while (equeue)
	{
		ft_printf("%s%s%s\n", "ls: ", equeue->folder,
			": No such file or directory");
		temp = equeue;
		equeue = equeue->next;
		free(temp->path);
		free(temp->folder);
		free(temp);
	}
	free(equeue);
}

void		ft_printfiles(t_queue *fque, int *info, int flag)
{
	t_queue	*temp;
	t_file	file;

	ft_foqueuesort(&fque, info);
	while (fque)
	{
		if (!info[0])
			ft_printf("%s\n", fque->folder);
		else
		{
			file = ft_info(ft_routecat(".", fque->folder), fque->folder, NULL);
			ft_printf("%s %u %s %s %lld %s %s", file.perm, file.links,
				file.owner, file.group, file.size, file.date, file.name);
			file.issymlink ? (ft_printf("%s%s\n", " -> ", file.symlinkname)) :
				(ft_printf("\n"));
			ft_freefile(&file);
		}
		temp = fque;
		fque = fque->next;
		ft_freetemp(temp);
	}
	free(fque);
	flag ? ft_printf("\n") : 0;
}

int			printdir(t_file *arr, int *info, int count, int idx)
{
	int		total;

	total = 0;
	if (info[0] && count)
	{
		while (++idx < count)
			total += arr[idx].blocks;
		if (count > 0)
			ft_printf("%s%d\n", "total ", total);
	}
	idx = -1;
	while (++idx < count)
	{
		if (info[0])
		{
			ft_printf("%s  %u %s  %s  %4lld %s %s", arr[idx].perm,
				arr[idx].links, arr[idx].owner, arr[idx].group, arr[idx].size,
				arr[idx].date, arr[idx].name);
			!arr[idx].issymlink ? (ft_printf("\n")) :
				(ft_printf("%s%s\n", " -> ", arr[idx].symlinkname));
		}
		else if (count || !info[0])
			ft_printf("%s\n", arr[idx].name);
	}
	return (total);
}
