/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 17:18:38 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/14 12:26:39 by cfelbacq         ###   ########.fr       */
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

int		check_env_name(t_list *env, char *name)
{
	t_list *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, name, ft_strlen(name)) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
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

void	check_curpath_dble_ar(char *curpath, t_list *env)
{
	if (access(curpath, F_OK) == -1)
	{
		ft_putstr("cd: No suck file or directory: ");
		ft_putendl(curpath);
	}
	else if (check_is_directory(curpath) == -1)
	{
		ft_putstr("cd: Not a directory: ");
		ft_putendl(curpath);
	}
	else if (access(curpath, X_OK) == -1)
	{
		ft_putstr("cd: Permission denied: ");
		ft_putendl(curpath);
	}
	else
	{
		ft_setenv(ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3)), env);
		ft_setenv(ft_strjoin("PWD=", curpath), env);
	}
}
