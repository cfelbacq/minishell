/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:19:16 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/16 19:59:23 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static	void	cd_dash(t_list **env, int p, char **v_pwd)
{
	char *tmp;
	char *oldpwd;
	char *curpath;

	if (check_env_name(*env, "OLDPWD") == 1 && ft_strlen(get_value_env(*env, "OLDPWD", 6)) != 0)
	{
		curpath = ft_strdup(get_value_env(*env, "OLDPWD", 6));
		tmp = ft_strdup(curpath);
		tmp = epur_slashe(tmp);
		if (check_tmp(tmp, p, tmp) == -1)
			return ;
		free(tmp);
		curpath = epur_path(curpath, p);
		ft_putendl(curpath);
		chdir(curpath);
		oldpwd = ft_strjoin("OLDPWD=", *v_pwd);
		tmp = ft_strjoin("PWD=", curpath);
		*env = ft_setenv(oldpwd, *env);
		*env = ft_setenv(tmp, *env);
		free(*v_pwd);
		*v_pwd = ft_strdup(curpath);
		free(curpath);
		free(tmp);
		free(oldpwd);
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
		tmp = ft_strdup(home);
		tmp = epur_slashe(tmp);
		if (check_tmp(tmp, p, home) == -1)
			return ;
		free(tmp);
		if (ft_strlen(home) != 0)
		{
			home = epur_path(home, p);
			chdir(home);
			oldpwd = ft_strjoin("OLDPWD=", *v_pwd);
			tmp = ft_strjoin("PWD=", home);
			*env = ft_setenv(oldpwd, *env);
			*env = ft_setenv(tmp, *env);
			free(*v_pwd);
			*v_pwd = ft_strdup(home);
			free(oldpwd);
			free(tmp);
		}
		free(home);
	}
	else
		ft_putendl_fd("cd: HOME not set", 2);
}

void			change_directory(t_list **start_env, char **ar, char **pwd)
{
	char	*curpath;
	int		i;
	int		p;

	curpath = NULL;
	i = 1;
	p = 0;
	cd_opt(&i, &p, ar);
	if (len_of_double_tab(ar) - i > 2)
		ft_putendl_fd("cd: too many arguments", 2);
	else if (len_of_double_tab(ar) - i == 2)// OK
		curpath = cd_double_ar(ar, start_env, p, i, pwd);
	else if (ft_strcmp(ar[i - 1], "-") == 0)// OK
		cd_dash(start_env, p, pwd);
	else if (ar[i] == NULL)// OK
		cd_home(start_env, p, pwd);
	else if (ar[i][0] == '/')// OK
		curpath = cd_slashe(ar[i], start_env, p, pwd);
	else if (ar[i][0] == '.' || ft_strcmp(ar[i], "..") == 0)// OK
		curpath = cd_dot(start_env, ar[i], p, pwd);
	else // OK
		curpath = cd_dir(start_env, ar[i], p, pwd);
//	ft_putstr("V_PWD");
//	ft_putendl(*pwd);
	chdir(curpath);
	free(curpath);
}
