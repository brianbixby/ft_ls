/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 07:39:37 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/08 07:39:38 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_freetemp(t_queue *temp)
{
	free(temp->path);
	free(temp->folder);
	free(temp);
}

void	ft_freefile(t_file *file)
{
	free(file->perm);
	free(file->date);
	free(file->name);
	if (file->issymlink)
		free(file->symlinkname);
}

void	ft_freemalloc(t_file *arr, int count, int size)
{
	int	idx;

	idx = 0;
	while (idx < count)
	{
		free(arr[idx].perm);
		free(arr[idx].name);
		free(arr[idx].date);
		if (arr[idx].issymlink)
			free(arr[idx].symlinkname);
		idx++;
	}
	idx = size;
	if (count)
		free(arr);
}

void	ft_instantiateidxarr(int *arr, int val, int size, int argc)
{
	int	i;

	i = -1;
	while (++i < size)
		arr[i] = val;
	arr[i] = argc;
}

void	ft_initializefile(t_file *file)
{
	file->perm = NULL;
	file->links = 0;
	file->owner = NULL;
	file->group = NULL;
	file->size = 0;
	file->name = NULL;
	file->nano = 0;
	file->issymlink = 0;
	file->symlinkname = NULL;
}
