/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listhelpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 05:03:32 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/18 05:03:34 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_queueobj		ft_listhelper(t_queue *q)
{
	t_queueobj	obj;

	obj.folder = q->folder;
	obj.path = q->path;
	obj.time = q->time;
	obj.nano = q->nano;
	obj.filfolarr = q->filfolarr;
	obj.count = q->count;
	obj.perm = q->perm;
	return (obj);
}

void			ft_listhelper2(t_queue *i, t_queue *j)
{
	i->folder = j->folder;
	i->path = j->path;
	i->time = j->time;
	i->nano = j->nano;
	i->filfolarr = j->filfolarr;
	i->count = j->count;
	i->perm = j->perm;
}

void			ft_listhelper3(t_queue *q, t_queueobj obj)
{
	q->folder = obj.folder;
	q->path = obj.path;
	q->time = obj.time;
	q->nano = obj.nano;
	q->filfolarr = obj.filfolarr;
	q->count = obj.count;
	q->perm = obj.perm;
}
