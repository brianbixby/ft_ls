/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_details.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 07:10:46 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/08 07:10:47 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	ft_getfiletype(mode_t perm)
{
	if (S_ISDIR(perm))
		return ('d');
	else if (S_ISCHR(perm))
		return ('c');
	else if (S_ISBLK(perm))
		return ('b');
	else if (S_ISSOCK(perm))
		return ('s');
	else if (S_ISFIFO(perm))
		return ('p');
	else if (S_ISLNK(perm))
		return ('l');
	else
		return ('-');
}

void	ft_getperms(mode_t perm, char *modeval)
{
	modeval[0] = ft_getfiletype(perm);
	modeval[1] = (perm & S_IRUSR) ? 'r' : '-';
	modeval[2] = (perm & S_IWUSR) ? 'w' : '-';
	modeval[3] = (perm & S_IXUSR) ? 'x' : '-';
	modeval[4] = (perm & S_IRGRP) ? 'r' : '-';
	modeval[5] = (perm & S_IWGRP) ? 'w' : '-';
	modeval[6] = (perm & S_IXGRP) ? 'x' : '-';
	modeval[7] = (perm & S_IROTH) ? 'r' : '-';
	modeval[8] = (perm & S_IWOTH) ? 'w' : '-';
	modeval[9] = (perm & S_IXOTH) ? 'x' : '-';
	modeval[10] = '\0';
	if (perm & S_ISUID)
		modeval[3] = (perm & S_IXUSR) ? 's' : 'S';
	if (perm & S_ISGID)
		modeval[6] = (perm & S_IXGRP) ? 's' : 'l';
	if (perm & S_ISVTX)
		modeval[9] = (perm & S_IXOTH) ? 't' : 'T';
}

char	*ft_readlink(char *filename, unsigned long long size, char *buf)
{
	ssize_t	nbytes;
	ssize_t	bufsize;

	bufsize = (!size ? 100 : size + 1);
	if (!(buf = (char *)malloc(sizeof(char) * bufsize)))
		return (NULL);
	if (!(nbytes = readlink(filename, buf, bufsize)))
		return (NULL);
	buf[nbytes] = '\0';
	return (buf);
}

t_file	ft_info(char *ptr, char *filename, char *modeval)
{
	struct stat st;
	t_file		file;

	ft_initializefile(&file);
	if (!(modeval = (char *)malloc(sizeof(char) * (11))))
		return (file);
	if (lstat(ptr, &st) == 0)
	{
		ft_getperms((mode_t)st.st_mode, modeval);
		file.perm = modeval;
		file.links = st.st_nlink;
		file.owner = getpwuid(st.st_uid)->pw_name;
		file.group = getgrgid(st.st_gid)->gr_name;
		file.size = st.st_size;
		file.blocks = st.st_blocks;
		file.date = ft_strsub(ctime(&st.st_mtime), (unsigned int)4, (size_t)12);
		file.name = ft_strdup(filename);
		file.time = st.st_mtime;
		file.nano = st.st_mtimespec.tv_nsec;
		file.issymlink = (modeval[0] == 'l') ? (1) : (0);
		if (modeval[0] == 'l')
			file.symlinkname = ft_readlink(ptr, file.size, file.symlinkname);
	}
	free(ptr);
	return (file);
}

void	ft_settime(char *name, char *concat, t_queue **foqueue, char *path)
{
	struct stat	st;
	char		c;

	c = name[0];
	if (lstat(concat, &st) == 0)
		ft_qpb(foqueue, ft_qobj(concat, st.st_mtime,
			st.st_mtimespec.tv_nsec, path));
	else
		ft_qpb(foqueue, ft_qobj(concat, (time_t)NULL, 0, path));
}
