/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreachdir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 01:42:49 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/18 01:42:51 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_getcurrentfilfolcount(int aflag, char *folder)
{
	int				count;
	struct dirent	*de;
	DIR				*dr;

	count = 0;
	dr = opendir(folder);
	while ((de = readdir(dr)) != NULL)
		if ((!aflag && (de->d_name[0] != '.')) || aflag)
			count++;
	closedir(dr);
	return (count);
}

void		ft_isd(char *fifo, char *concat, t_queue **foqueue, char *path)
{
	struct stat		st;

	if (lstat(concat, &st) == 0)
	{
		if (S_ISDIR((mode_t)st.st_mode))
			ft_settime(fifo, concat, foqueue, path);
		else
			free(path);
	}
	else
		free(path);
}

int			ft_hasperms(char *folder)
{
	struct stat		st;

	if (lstat(folder, &st) == 0)
		return (((mode_t)st.st_mode & S_IRUSR) ? 1 : 0);
	return (1);
}

int			ft_foreachdirhelper(int *info, t_file *filfolarr,
				int count, t_queue **foqueue)
{
	if (info[3])
		info[2] ? (ft_revdatesort(filfolarr, count)) :
			(ft_datesort(filfolarr, count));
	else
		info[2] ? (ft_namesort(filfolarr, count, 1)) :
			(ft_namesort(filfolarr, count, 0));
	ft_freemalloc(filfolarr, count, printdir(filfolarr, info, count, -1));
	if ((*foqueue)->next)
		ft_printf("\n");
	return (1);
}

int			ft_foreachdir(int *info, t_queue **fq,
				t_queue *tq, int i)
{
	int				count;
	struct dirent	*de;
	t_file			*filfolarr;
	DIR				*dr;
	char			*str;

	if (!(ft_hasperms((*fq)->folder)))
		return (ft_printpermden((*fq)->path, fq));
	count = ft_getcurrentfilfolcount(info[1], (*fq)->folder);
	dr = opendir((*fq)->folder);
	if (!(filfolarr = (t_file *)malloc(sizeof(t_file) * count)))
		return (0);
	while ((de = readdir(dr)) != NULL)
	{
		if ((!info[1] && (de->d_name[0] != '.')) || info[1])
		{
			str = ft_routecat((*fq)->folder, de->d_name);
			if (info[4] && ft_cmp(de->d_name, ".") && ft_cmp(de->d_name, ".."))
				ft_isd(de->d_name, str, &tq, ft_pcat((*fq)->path, de->d_name));
			filfolarr[++i] = ft_info(str, de->d_name, NULL);
		}
	}
	closedir(dr);
	ft_queuecombine(fq, &tq, info);
	return (ft_foreachdirhelper(info, filfolarr, count, fq));
}
