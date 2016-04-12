/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 17:31:09 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/12 17:57:09 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_slashe(char *ar, t_list *env, int p)
{
	char *curpath;

	curpath = ft_strdup(ar);
		curpath = epur_path(curpath, p);
	if (access(curpath, F_OK) == -1)
		print_cd_err(1, ar);
	else if (check_is_directory(curpath) == -1)
		print_cd_err(2, ar);
	else if (access(curpath, X_OK) == -1)
		print_cd_err(3, ar);
	else
	{
	//	curpath = epur_path(curpath, p);
		ft_setenv(ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3)), env);
		ft_setenv(ft_strjoin("PWD=", curpath), env);
	}
	return (curpath);
}

char	*cd_dot(t_list *env, char *ar, int p)
{
	char *curpath;

	curpath = NULL;
	curpath = ft_strjoin(ft_strjoin(get_value_env(env, "PWD", 3), "/"), ar);
	curpath = epur_path(curpath, p);
	if (access(curpath, F_OK) == -1)
		print_cd_err(1, ar);
	else if (check_is_directory(curpath) == -1)
		print_cd_err(2, ar);
	else if (access(curpath, X_OK) == -1)
		print_cd_err(3, ar);
	else
	{
	//	curpath = epur_path(curpath, p);
		ft_setenv(ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3)), env);
		ft_setenv(ft_strjoin("PWD=", curpath), env);
	}
	return (curpath);
}

char	*cd_dir(t_list *env, char *ar, int p)
{
	char *curpath;

	curpath = ft_strdup(getcwd(NULL, 0));
	curpath = ft_strjoin(curpath, "/");
	curpath = ft_strjoin(curpath, ar);
	curpath = epur_path(curpath, p);
	if (access(curpath, F_OK) == -1)
		print_cd_err(1, ar);
	else if (check_is_directory(curpath) == -1)
		print_cd_err(2, ar);
	else if (access(curpath, X_OK) == -1)
		print_cd_err(3, ar);
	else
	{
	//	curpath = epur_path(curpath, p);
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

	tmp = ft_strsplit(getcwd(NULL, 0), '/');
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
	ft_putstr_fd("cd: string not in pwd: ", 2);
	ft_putendl_fd(ar[1], 2);
	return (NULL);
}
