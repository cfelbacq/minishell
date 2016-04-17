/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:19:16 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/17 16:19:22 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	free_cd(char **v_pwd, char *curpath, char *tmp, char *oldpwd)
{
	free(*v_pwd);
	*v_pwd = ft_strdup(curpath);
	free(curpath);
	free(tmp);
	free(oldpwd);
}

static	void	cd_dash(t_list **env, int p, char **v_pwd)
{
	char *tmp;
	char *oldpwd;
	char *curpath;

	if (check_env_name(*env, "OLDPWD") == 1 &&\
			ft_strlen(get_value_env(*env, "OLDPWD", 6)) != 0)
	{
		curpath = ft_strdup(get_value_env(*env, "OLDPWD", 6));
		tmp = epur_slashe(ft_strdup(curpath));
		if (check_tmp(tmp, p, tmp) == -1)
			return (free(curpath));
		free(tmp);
		curpath = epur_path(curpath, p);
		ft_putendl(curpath);
		chdir(curpath);
		oldpwd = ft_strjoin("OLDPWD=", *v_pwd);
		tmp = ft_strjoin("PWD=", curpath);
		*env = ft_setenv(oldpwd, *env);
		*env = ft_setenv(tmp, *env);
		return (free_cd(v_pwd, curpath, tmp, oldpwd));
	}
	else
		ft_putendl_fd("cd: OLDPWD not set", 2);
}

static	void	cd_home(t_list **env, int p, char **v_pwd)
{
	char *home;
	char *oldpwd;
	char *tmp;

	if (check_env_name(*env, "HOME") == 1)
	{
		home = ft_strdup(get_value_env(*env, "HOME", 4));
		tmp = epur_slashe(ft_strdup(home));
		if (check_tmp(tmp, p, home) == -1)
			return (free(home));
		free(tmp);
		if (ft_strlen(home) != 0)
		{
			home = epur_path(home, p);
			chdir(home);
			oldpwd = ft_strjoin("OLDPWD=", *v_pwd);
			tmp = ft_strjoin("PWD=", home);
			*env = ft_setenv(oldpwd, *env);
			*env = ft_setenv(tmp, *env);
			return (free_cd(v_pwd, home, tmp, oldpwd));
		}
		free(home);
	}
	else
		ft_putendl_fd("cd: HOME not set", 2);
}

void			change_directory(t_list **start_env, char **ar, char **pwd)
{
	char		*curpath;
	t_two_int	integer;

	curpath = NULL;
	integer.i = 1;
	integer.p = 0;
	cd_opt(&integer.i, &integer.p, ar);
	if (len_of_double_tab(ar) - integer.i > 2)
		ft_putendl_fd("cd: too many arguments", 2);
	else if (len_of_double_tab(ar) - integer.i == 2)
		curpath = cd_double_ar(ar, start_env, integer, pwd);
	else if (ft_strcmp(ar[integer.i - 1], "-") == 0)
		cd_dash(start_env, integer.p, pwd);
	else if (ar[integer.i] == NULL)
		cd_home(start_env, integer.p, pwd);
	else if (ar[integer.i][0] == '/')
		curpath = cd_slashe(ar[integer.i], start_env, integer.p, pwd);
	else if (ar[integer.i][0] == '.' || ft_strcmp(ar[integer.i], "..") == 0)
		curpath = cd_dot(start_env, ar[integer.i], integer.p, pwd);
	else
		curpath = cd_dir(start_env, ar[integer.i], integer.p, pwd);
	chdir(curpath);
	free(curpath);
}
