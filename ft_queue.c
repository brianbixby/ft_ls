/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 12:26:39 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/08 12:26:41 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_queue			*ft_createelem(t_queueobj obj)
{
	t_queue		*tmp;

	if (!(tmp = (t_queue *)malloc(sizeof(t_queue))))
		return (NULL);
	if (ft_strcmp(obj.folder, "/") == 0)
		obj.folder = "./";
	tmp->folder = ft_strdup(obj.folder);
	tmp->path = (obj.path ? obj.path : ft_strdup(obj.folder));
	tmp->time = obj.time;
	tmp->nano = obj.nano;
	tmp->next = NULL;
	return (tmp);
}

void			ft_qpb(t_queue **begin_queue, t_queueobj obj)
{
	t_queue *queue;

	if (begin_queue && *begin_queue)
	{
		queue = *begin_queue;
		while (queue->next)
			queue = queue->next;
		queue->next = ft_createelem(obj);
	}
	else
		*begin_queue = ft_createelem(obj);
}

void			ft_queuecombine(t_queue **begin_queue, t_queue **new_queue,
					int *info)
{
	t_queue	*dup;
	t_queue	*tmp;

	if (*new_queue)
		ft_foqueuesort(new_queue, info);
	dup = *new_queue;
	tmp = *begin_queue;
	tmp = tmp->next;
	if (!(new_queue && *new_queue))
		return ;
	if (begin_queue && *begin_queue)
	{
		while (dup->next)
			dup = dup->next;
		dup->next = tmp;
		(*begin_queue)->next = (*new_queue);
	}
	else
		*begin_queue = *new_queue;
}

t_queueobj		ft_qobj(char *folder, time_t ttime, long long nano, char *path)
{
	t_queueobj	obj;

	obj.folder = folder;
	obj.time = ttime;
	obj.nano = nano;
	obj.path = path;
	return (obj);
}
