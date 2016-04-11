/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 17:31:09 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/11 19:40:23 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_slashe(char *ar, t_list *env, int p)
{
	char *curpath;

	curpath = ft_strdup(ar);
	ft_putendl(curpath);
	if (access(curpath, F_OK) == -1)
	{
		ft_putstr("cd: No suck file or directory: ");
		ft_putendl(ar);
	}
	else if (check_is_directory(curpath) == -1)
	{
		ft_putstr("cd: Not a directory: ");
		ft_putendl(ar);
	}
	else if (access(curpath, R_OK) == -1)
	{
		ft_putstr("cd: Permission denied: ");
		ft_putendl(ar);
	}
	else
	{
		curpath = epur_path(curpath, p);
		ft_putstr("PATH EPUR : ");
		ft_putendl(curpath);
		ft_setenv(ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3)), env);
		ft_setenv(ft_strjoin("PWD=", curpath), env);
	}
	return (curpath);
}

char	*cd_dot(t_list *env, char *ar, int p)
{
	char *curpath;

	ft_putchar('a');
	curpath = NULL;
	curpath = ft_strjoin(ft_strjoin(get_value_env(env, "PWD", 3), "/"), ar);
	ft_putendl(curpath);
	if (access(curpath, F_OK) == -1)
	{
		ft_putstr("cd: No suck file or directory: ");
		ft_putendl(ar);
	}
	else if (check_is_directory(curpath) == -1)
	{
		ft_putstr("cd: Not a directory: ");
		ft_putendl(ar);
	}
	else if (access(curpath, R_OK) == -1)
	{
		ft_putstr("cd: Permission denied: ");
		ft_putendl(ar);
	}
	else
	{
		curpath = epur_path(curpath, p);
		ft_putstr("PATH EPUR : ");
		ft_putendl(curpath);
		ft_setenv(ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3)), env);
		ft_setenv(ft_strjoin("PWD=", curpath), env);
	}
	return (curpath);
}

char	*cd_dir(t_list *env, char *ar, int p)
{
	char *curpath;

	curpath = ft_strdup(get_value_env(env, "PWD", 3));
	curpath = ft_strjoin(curpath, "/");
	curpath = ft_strjoin(curpath, ar);
	ft_putendl(curpath);
	if (access(curpath, F_OK) == -1)
	{
		ft_putstr("cd: No suck file or directory: ");
		ft_putendl(ar);
	}
	else if (check_is_directory(curpath) == -1)
	{
		ft_putstr("cd: Not a directory: ");
		ft_putendl(ar);
	}
	else if (access(curpath, R_OK) == -1)
	{
		ft_putstr("cd: Permission denied: ");
		ft_putendl(ar);
	}
	else
	{
		curpath = epur_path(curpath, p);
		ft_putstr("PATH EPUR : ");
		ft_putendl(curpath);
		ft_setenv(ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3)), env);
		ft_setenv(ft_strjoin("PWD=", curpath), env);
	}
	return (curpath);
}

char	*cd_double_ar(char **ar, t_list *env, int p)
{
	char	**tmp;
	t_list	*tmp2;
	int		i;

	tmp = ft_strsplit(get_value_env(env, "PWD", 3), '/');
	tmp2 = init_env(tmp);
	tmp2 = epur_list(tmp2);
	tmp = lst_to_tab(tmp2);
	tmp2 = NULL;
	i = 0;
	while (tmp[i] != NULL)
	{
		if (ft_strcmp(tmp[i], ar[1]) == 0)
		{
			free(tmp[i]);
			tmp[i] = ft_strdup(ar[2]);
			tmp2 = init_env(tmp);
			check_curpath_dble_ar(ins_slashes(tmp2, p), env);
			return (ins_slashes(tmp2, p));
		}
		i++;
	}
	ft_putstr("cd: string not in pwd: ");
	ft_putendl(ar[1]);
	return (NULL);
}
