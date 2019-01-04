/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 00:06:34 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/07 00:06:40 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	*ft_getinfohelper(int *info, int i, int flag)
{
	if (flag)
		info[5] = i;
	else if (i > 1 && !info[0] && !info[1] && !info[2] && !info[3] && !info[4])
		info[5] = 1;
	return (info);
}

int			*ft_getinfo(int argc, char **av, int *info, int i)
{
	int		j;

	while (++i < argc)
	{
		j = 0;
		if (av[i][0] != '-')
			return (ft_getinfohelper(info, i, 1));
		while (av[i][++j])
		{
			if (av[i][j] == 'l')
				info[0] = 1;
			else if (av[i][j] == 'a')
				info[1] = 1;
			else if (av[i][j] == 'r')
				info[2] = 1;
			else if (av[i][j] == 't')
				info[3] = 1;
			else if (av[i][j] == 'R')
				info[4] = 1;
			else
				return (ft_printnomatches(av[i], info, av[i][j]));
		}
	}
	return (ft_getinfohelper(info, i, 0));
}

int			main(int argc, char **av)
{
	int				info[7];
	int				count;
	t_queue			*foqueue;
	t_queue			*temp;

	ft_instantiateidxarr(info, 0, 6, argc);
	count = -1;
	foqueue = NULL;
	*info = *ft_getinfo(argc, av, info, 0);
	if (info[0] == -1)
		return (1);
	argc == 1 || !info[5] ? ft_qpb(&foqueue, ft_qobj(".", (time_t)NULL, 0,
		ft_strdup("."))) : ft_seterfifo(av, info, &foqueue, &count);
	if (foqueue)
		ft_foqueuesort(&foqueue, info);
	while (foqueue)
	{
		if (++count || foqueue->next)
			ft_printf("%s%c\n", foqueue->path, ':');
		ft_foreachdir(info, &foqueue, NULL, -1);
		temp = foqueue;
		foqueue = foqueue->next;
		ft_freetemp(temp);
	}
	return (0);
}
