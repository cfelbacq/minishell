/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:19:16 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/15 15:14:00 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	cd_dash(t_list *env, int p)
{
	char *tmp;
	char *oldpwd;
	char *pwd;

	if (check_env_name(env, "OLDPWD") == 1)
	{
		tmp = ft_strdup(get_value_env(env, "OLDPWD", 6));
		tmp = epur_slashe(tmp);
		if (check_tmp(tmp, p, tmp) == -1)
			return ;
		if (ft_strlen(tmp) != 0)
		{
			tmp = epur_path(tmp, p);
			chdir(tmp);
			oldpwd = ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3));
			pwd = ft_strjoin("PWD=", tmp);
			ft_setenv(oldpwd, env);
			ft_setenv(pwd, env);
			ft_putendl(get_value_env(env, "PWD", 3));
			free(pwd);
			free(oldpwd);
		}
	}
	else
		ft_putendl_fd("cd: OLDPWD not set", 2);
}

static	void	cd_home(t_list *env, int p)
{
	char *home;
	char *oldpwd;
	char *pwd;

	if (check_env_name(env, "HOME") == 1)
	{
		home = ft_strdup(get_value_env(env, "HOME", 4));
		home = epur_slashe(home);
		if (check_tmp(home, p, home) == -1)
			return ;
		if (ft_strlen(home) != 0)
		{
			home = epur_path(home, p);
			chdir(home);
			oldpwd = ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3));
			pwd = ft_strjoin("PWD=", home);
			ft_setenv(oldpwd, env);
			ft_setenv(pwd, env);
			free(oldpwd);
			free(pwd);
			free(home);
		}
	}
	else
		ft_putendl_fd("cd: HOME not set", 2);
}

void			change_directory(t_list *start_env, char **ar)
{
	char	*curpath;
	int		i;
	int		p;

	curpath = NULL;
	i = 1;
	p = 0;
	cd_opt(&i, &p, ar);
	//ft_setenv(ft_strjoin("PWD=", getcwd(NULL, 0)), start_env);
	if (len_of_double_tab(ar) - i > 2)
		ft_putendl_fd("cd: too many arguments", 2);
	else if (len_of_double_tab(ar) - i == 2)
		curpath = cd_double_ar(ar, start_env, p, i);
	else if (ft_strcmp(ar[i - 1], "-") == 0)
		cd_dash(start_env, p);
	else if (ar[i] == NULL)
		cd_home(start_env, p);
	else if (ar[i][0] == '/')
		curpath = cd_slashe(ar[i], start_env, p);
	else if (ar[i][0] == '.' || ft_strcmp(ar[i], "..") == 0)
		curpath = cd_dot(start_env, ar[i], p);
	else
		curpath = cd_dir(start_env, ar[i], p);
	if (curpath != NULL)
		ft_putendl(curpath);
	chdir(curpath);
	free(curpath);
}
