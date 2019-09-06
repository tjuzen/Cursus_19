/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 12:55:14 by tjuzen            #+#    #+#             */
/*   Updated: 2019/09/04 13:44:48 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		init_arg(t_arg_ls *arg)
{
	arg->is_l = 0;
	arg->is_rr = 0;
	arg->is_a = 0;
	arg->is_r = 0;
	arg->is_t = 0;
	if (!(arg->path = ft_strdup("./")))
		return (-1);
	arg->totalsize = 0;
	arg->flag_mutiple_folders = 0;
	arg->file_printed = 0;
	arg->is_in_recu = 0;
	return (0);
}

void	init_arg_2(t_arg_lsbig *arg)
{
	arg->big_hard = 0;
	arg->big_pw = 0;
	arg->big_gr = 0;
	arg->big_size = 0;
	arg->big_size_maj = 0;
	arg->have_maj_min = 0;
}

int		check_path(char *str, t_arg_ls *arg)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	if (!(arg->path = ft_strjoin(str, "/")))
		return (-1);
	return (1);
}

int		check_point(char *s)
{
	int			i;
	size_t		len;

	i = 0;
	len = ft_strlen(s);
	len--;
	while (s[len] != '/' && s[len] != '.')
		len--;
	while (s[len] != '/' && s[len] == '.')
	{
		i++;
		len--;
	}
	if (i == 1 || i == 2)
	{
		if ((ft_strlen(s)) - 3 <= len)
			return (1);
	}
	return (0);
}
