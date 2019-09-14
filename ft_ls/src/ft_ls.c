/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 12:02:01 by tjuzen            #+#    #+#             */
/*   Updated: 2019/09/14 18:20:44 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		recursive_dir(t_arg_ls *arg, t_list_ls *mylist)
{
	struct stat	fs;
	char		*tmp;

	tmp = arg->path;
	while (mylist != NULL)
	{
		if (!(mylist->file_name_path = ft_strjoin(tmp, mylist->file_name)))
			return (-1);
		if (lstat(mylist->file_name_path, &fs) < 0)
			return (0);
		if (S_ISDIR(fs.st_mode) && ft_strcmp(mylist->file_name, ".") && ft_strcmp(mylist->file_name, ".."))
		{
				if (!(arg->path = ft_strjoin(mylist->file_name_path, "/")))
					return (-1);
				ft_printf("\n%s:\n", mylist->file_name_path);
				arg->totalsize = 0;
				if (handle_arg(arg) == 1)
				{
					ft_strdel(&tmp);
					return (-1);
				}
		}
		mylist = mylist->next;
	}
	ft_strdel(&tmp);
	return (0);
}

t_list_ls	*params(t_list_ls *mylist, t_arg_ls *arg)
{
	DIR		*d;
	struct	dirent *dir;

	d = NULL;
	dir = NULL;
	mylist = push(mylist, arg, d, dir);
	mylist = sort_ascii(mylist);
	return (mylist);
}

int		handle_arg(t_arg_ls *arg)
{
	t_list_ls		*mylist;

	mylist = NULL;
	mylist = params(mylist, arg);
	if ((mylist == NULL && (arg->malloc_error == 1)))
		return (1);
	if (mylist != NULL)
	{
		if (arg->is_t == 1)
			mylist = sort_time(mylist);
		if (arg->is_r == 1)
			mylist = reverse_list(mylist);
		if (arg->is_l != 1)
			print_list(mylist);
		else
			print_full_list(mylist, arg, 0);
	}
	if (arg->is_rr)
	{
		arg->is_in_recu = 1;
		if (recursive_dir(arg, mylist) == -1)
			return (free_list(mylist, 1));
	}
	return (free_list(mylist, 0));
}

int			free_all(t_list_ls *list_dir, t_list_ls *list_file, t_arg_ls *arg)
{
	free_list(list_file, 0);
	free_list_dir(list_dir, 0);
	if (arg->is_rr == 0)
		free_struct_arg(arg);
	return (1);

}

int			main(int argc, char **argv)
{
	t_arg_ls		arg;
	t_list_ls		*mylistdir;
	t_list_ls		*mylistfile;
	int				i;

	mylistdir = NULL;
	mylistfile = NULL;
	i = 0;
	if (init_arg(&arg) == -1)
		return (1);
	if ((i = check_options(1, argc, argv, &arg)) == -1)
		return (free_struct_arg(&arg));
	if (i == argc)
	{
		i = handle_arg(&arg);
		if (arg.is_rr == 0)
			free_struct_arg(&arg);
		return (i);
	}
	if (argc - i > 1)
		arg.flag_mutiple_folders = 1;
	mylistfile = fill_file(i, argc, argv, &arg);
	display_my_files(mylistfile, &arg);
	mylistdir = fill_dir(i, argc, argv, &arg);
	if (display_my_dir(mylistdir, &arg) == -1)
		return (free_all(mylistdir, mylistfile, &arg));
	free_all(mylistdir, mylistfile, &arg);
	return (0);
}
