/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 17:18:38 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/16 20:09:08 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_opt(int *i, int *p, char **ar)
{
	int j;

	j = 0;
	while (ar[*i] != NULL && ar[*i][0] == '-')
	{
		j = 0;
		if (check_opt(ar[*i]) == 1)
		{
			while (ar[*i][j] != '\0')
			{
				if (j >= 1 && ar[*i][j] == 'P')
					*p = 1;
				else if (j >= 1 && ar[*i][j] == 'L')
					*p = 0;
				j++;
			}
			*i = *i + 1;
		}
		else
		{
			p = 0;
			return ;
		}
	}
	return ;
}

int		check_opt(char *str)
{
	int i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'P' && str[i] != 'L')
			return (0);
		i++;
	}
	return (1);
}

int		check_is_directory(char *curpath)
{
	struct stat buf;

	lstat(curpath, &buf);
	if ((buf.st_mode & S_IFMT) == S_IFDIR \
			|| ((buf.st_mode & S_IFMT) == S_IFLNK && opendir(curpath) != NULL))
		return (0);
	else
		return (-1);
}

int	error_check_tmp(char *tmp, char *new, char **doubletab, char *ar)
{
	if (access(new, F_OK) == -1)
	{
		print_cd_err(1, ar);
		free(tmp);
		free(new);
		free_double_tab(doubletab);
		return (-1);
	}
	else if (check_is_directory(new) == -1)
	{
		print_cd_err(2, ar);
		free(tmp);
		free(new);
		free_double_tab(doubletab);
		return (-1);
	}
	else if (access(new, X_OK) == -1)
	{
		print_cd_err(3, ar);
		free(tmp);
		free(new);
		free_double_tab(doubletab);
		return (-1);
	}
	return (0);
}

int		check_tmp(char *tmp, int p, char *ar)
{
	char	**tmp_double;
	char	*new;
	int		i;

	i = 0;
	tmp_double = ft_strsplit(tmp, '/');
	new = (char *)ft_memalloc(sizeof(char) * ft_strlen(tmp) + 1);
	while (tmp_double[i] != NULL)
	{
		if (ft_strcmp(new, "/") != 0)
			new = ft_stradd(new, "/");
		new = ft_stradd(new, tmp_double[i]);
		if (error_check_tmp(tmp, new, tmp_double, ar) == -1)
			return (-1);
		new = epur_path(new, p);
		i++;
	}
	free_double_tab(tmp_double);
	free(new);
	return (0);
}
