/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 00:06:50 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/07 00:06:51 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_isfile(char *filename)
{
	struct stat	buf;

	return (stat(filename, &buf) == 0);
}

int		ft_isdir(char *dirname)
{
	struct stat		st;

	if (lstat(dirname, &st) == 0)
		return (S_ISDIR((mode_t)st.st_mode) ? 1 : 0);
	return (0);
}

void	ft_seterfifo(char **av, int *info, t_queue **foqueue, int *count)
{
	t_queue	*equ;
	t_queue	*fqu;
	int		i;
	int		flag;

	equ = NULL;
	fqu = NULL;
	i = info[5] - 1;
	while (++i < info[6])
	{
		if (!ft_isdir(av[i]))
			ft_isfile(av[i]) ? ft_settime(av[i], av[i], &fqu, ft_strdup(av[i]))
			: (ft_qpb(&equ, ft_qobj(av[i], (time_t)NULL, 0, NULL)));
		else
		{
			info[3] ? ft_settime(av[i], av[i], foqueue, ft_strdup(av[i])) :
			ft_qpb(foqueue, ft_qobj(av[i], (time_t)NULL, 0, ft_strdup(av[i])));
		}
	}
	flag = ((*foqueue) ? 1 : 0);
	*count += (equ || fqu ? 1 : 0);
	if (equ)
		ft_printerrors(equ);
	if (fqu)
		ft_printfiles(fqu, info, flag);
}
