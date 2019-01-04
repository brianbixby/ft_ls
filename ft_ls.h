/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbixby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 00:07:06 by bbixby            #+#    #+#             */
/*   Updated: 2018/12/07 00:07:07 by bbixby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "./ft_printf/ft_printf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <errno.h>
# include <dirent.h>
# include <stdio.h>

typedef struct			s_file
{
	char				*perm;
	unsigned int		links;
	char				*owner;
	char				*group;
	unsigned long long	size;
	char				*date;
	char				*name;
	int					error;
	time_t				time;
	long long			nano;
	int					issymlink;
	char				*symlinkname;
	int					blocks;
}						t_file;

typedef struct			s_queueobj
{
	char				*folder;
	char				*path;
	time_t				time;
	long long			nano;
	t_file				*filfolarr;
	int					count;
	int					perm;
}						t_queueobj;

typedef struct			s_queue
{
	struct s_queue		*next;
	char				*folder;
	char				*path;
	time_t				time;
	long long			nano;
	t_file				*filfolarr;
	int					count;
	int					perm;
}						t_queue;

/*
** main.c
*/
int						*ft_getinfo(int argc, char **av, int *info, int i);

/*
** ft_foreachdir.c
*/
int						ft_getcurrentfilfolcount(int aflag, char *folder);
int						ft_foreachdirhelper(int *info, t_file *filfolarr,
							int count, t_queue **foqueue);
int						ft_foreachdir(int *info, t_queue **foqueue,
							t_queue *tempqueue, int i);
void					ft_isd(char *fifo, char *concat, t_queue **foqueue,
							char *path);
int						ft_hasperms(char *concat);

/*
** ft_errors.c
*/
int						ft_isfile(char *filename);
int						ft_isdir(char *dirname);
void					ft_seterfifo(char **av, int *info, t_queue **foqueue,
							int *count);

/*
** ft_details.c
*/
char					ft_getfiletype(mode_t perm);
void					ft_getperms(mode_t perm, char *modeval);
char					*ft_readlink(char *filename, unsigned long long size,
							char *buf);
t_file					ft_info(char *ptr, char *filename,
							char *modeval);
void					ft_settime(char *name, char *concat, t_queue **foqueue,
							char *path);

/*
** ft_prints.c
*/
void					ft_printerrors(t_queue *equeue);
int						*ft_printnomatches(char *av, int *info, char option);
void					ft_printfiles(t_queue *fque, int *info, int flag);
int						printdir(t_file *arr, int *info, int count, int idx);
int						ft_printpermden(char *folder, t_queue **foqueue);

/*
** ft_sorts.c
*/
void					ft_wordsort(char **tab, int len, int rev);
void					ft_namesort(t_file *foarr, int len, int rev);
void					ft_datesort(t_file *foarr, int len);
void					ft_revdatesort(t_file *foarr, int len);
void					ft_foarrsort(t_file *foarr, int *info, int count);

/*
** ft_sorts2.c
*/
void					ft_list_sort(t_queue **begin_list, int rev);
void					ft_list_datesort(t_queue **begin_list);
void					ft_revlist_datesort(t_queue **begin_list);
void					ft_foqueuesort(t_queue	**foqueue, int *info);

/*
** ft_listhelpers.c
*/
t_queueobj				ft_listhelper(t_queue *q);
void					ft_listhelper2(t_queue *i, t_queue *j);
void					ft_listhelper3(t_queue *q, t_queueobj obj);

/*
** ft_helpers1.c
*/
size_t					ft_strle(const char *s);
int						ft_cmp(char *s1, char *s2);
char					*ft_strsub(char const *s, unsigned int start,
							size_t len);
char					*ft_pcat(char *s1, char *s2);

/*
** ft_routecat.c
*/
char					*ft_routecat(char *s1, char *s2);
char					*ft_routecat2(char *s1);
char					*ft_routecat3(char *s1, char *s2);

/*
** ft_free.c
*/
void					ft_freetemp(t_queue *temp);
void					ft_freefile(t_file *file);
void					ft_freemalloc(t_file *arr, int count, int size);
void					ft_instantiateidxarr(int *arr, int val, int size,
							int argc);
void					ft_initializefile(t_file *file);

/*
** ft_queue.c
*/
t_queue					*ft_createelem(t_queueobj obj);
void					ft_qpb(t_queue **begin_queue, t_queueobj obj);
void					ft_queuecombine(t_queue **begin_queue,
							t_queue **new_queue, int *info);
t_queueobj				ft_qobj(char *folder, time_t ttime, long long nano,
							char *path);

#endif
