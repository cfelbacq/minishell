/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:19:16 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/12 14:03:18 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	cd_dash(t_list *env)
{
	char *tmp;

	tmp = NULL;
	if (check_env_name(env, "OLDPWD") == 1)
	{
		tmp = ft_strdup(get_value_env(env, "OLDPWD", 6));
		chdir(get_value_env(env, "OLDPWD", 6));
		ft_setenv(ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3)), env);
		ft_setenv(ft_strjoin("PWD=", tmp), env);
		ft_putendl(get_value_env(env, "PWD", 3));
	}
	else
		ft_putendl_fd("cd: OLDPWD not set", 2);
}

static	void	cd_home(t_list *env)
{
	if (check_env_name(env, "HOME") == 1)
	{
		chdir(get_value_env(env, "HOME", 4));
		ft_setenv(ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3)), env);
		ft_setenv(ft_strjoin("PWD=", get_value_env(env, "HOME", 4)), env);
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
		curpath = cd_double_ar(ar, start_env, p);
	else if (ft_strcmp(ar[i - 1], "-") == 0)
		cd_dash(start_env);
	else if (ar[i] == NULL)
		cd_home(start_env);
	else if (ar[i][0] == '/')
		curpath = cd_slashe(ar[i], start_env, p);
	else if (ar[i][0] == '.' || ft_strcmp(ar[i], "..") == 0)
		curpath = cd_dot(start_env, ar[i], p);
	else
		curpath = cd_dir(start_env, ar[i], p);
	if (curpath != NULL)
		ft_putendl(curpath);
	chdir(curpath);
}
