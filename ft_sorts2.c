/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorts2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 01:38:03 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/18 01:38:05 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_list_sort(t_queue **begin_list, int rev)
{
	t_queue		*i;
	t_queue		*j;
	t_queueobj	temp;

	i = *begin_list;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (!rev ? (ft_strcmp(i->folder, j->folder) > 0) :
				(ft_strcmp(i->folder, j->folder) < 0))
			{
				temp = ft_listhelper(i);
				ft_listhelper2(i, j);
				ft_listhelper3(j, temp);
			}
			j = j->next;
		}
		i = i->next;
	}
}

void	ft_revlist_datesort(t_queue **begin_list)
{
	t_queue		*i;
	t_queue		*j;
	t_queueobj	temp;

	i = *begin_list;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (i->time > j->time ||
			(i->time == j->time && i->nano > j->nano) ||
			(i->time == j->time && i->nano == j->nano &&
			ft_strcmp(i->folder, j->folder) < 0))
			{
				temp = ft_listhelper(i);
				ft_listhelper2(i, j);
				ft_listhelper3(j, temp);
			}
			j = j->next;
		}
		i = i->next;
	}
}

void	ft_list_datesort(t_queue **begin_list)
{
	t_queue		*i;
	t_queue		*j;
	t_queueobj	temp;

	i = *begin_list;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (i->time < j->time ||
			(i->time == j->time && i->nano < j->nano) ||
			(i->time == j->time && i->nano == j->nano &&
			ft_strcmp(i->folder, j->folder) > 0))
			{
				temp = ft_listhelper(i);
				ft_listhelper2(i, j);
				ft_listhelper3(j, temp);
			}
			j = j->next;
		}
		i = i->next;
	}
}

void	ft_foqueuesort(t_queue **foqueue, int *info)
{
	if (info[3])
		info[2] ? (ft_revlist_datesort(foqueue)) :
			(ft_list_datesort(foqueue));
	else
		info[2] ? ft_list_sort(foqueue, 1) : ft_list_sort(foqueue, 0);
}
