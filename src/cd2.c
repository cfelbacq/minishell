/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 17:31:09 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/13 16:59:06 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*epur_slashe(char *tmp);
int		check_tmp(char *tmp, char p);

char	*cd_slashe(char *ar, t_list *env, int p)
{
	char *curpath;
	char *tmp;

	curpath = ft_strdup(ar);
	tmp = curpath;
	curpath = epur_path(curpath, p);
	if (check_tmp(epur_slashe(tmp), p) == -1)
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

char	*epur_slashe(char *tmp)
{
	char *new;
	int i;
	int j;

	j = 0;
	new = (char *)ft_memalloc(sizeof(char) * ft_strlen(tmp) + 1);
	i = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '/')
		{
			new[j++] = tmp[i++];
			while (tmp[i] == '/')
				i++;
		}
		new[j] = tmp[i];
		j++;
		i++;
	}
	new[j] = '\0';
	return (new);
}

int		check_tmp(char *tmp, char p)
{
	char **tmp_double;
	char *new;
	int i;

	 i = 0;
	ft_putendl(tmp);
	tmp_double = ft_strsplit(tmp, '/');
	new = (char *)ft_memalloc(sizeof(char) * ft_strlen(tmp));
	while (tmp_double[i] != NULL)
	{
		if (ft_strcmp(new, "/") != 0)
			new = ft_strcat(new, "/");
		new = ft_strjoin(new, tmp_double[i]);
		ft_putstr("NEW :");
		ft_putendl(new);
		if (access(new, F_OK) == -1)
			return (-1);
		new = epur_path(new, p);
		i++;
	}
	return (0);
}

char	*cd_dot(t_list *env, char *ar, int p)
{
	char *curpath;
	char *tmp;


	curpath = NULL;
	curpath = ft_strjoin(ft_strjoin(get_value_env(env, "PWD", 3), "/"), ar);
	tmp = curpath;
	curpath = epur_path(curpath, p);
	if (check_tmp(epur_slashe(tmp), p) == -1)
		print_cd_err(1, ar);
	else if (check_is_directory(curpath) == -1)
		print_cd_err(2, ar);
	else if (access(curpath, X_OK) == -1)
		print_cd_err(3, ar);
	else
	{
		curpath = epur_path(curpath, p);
		ft_setenv(ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3)), env);
		ft_setenv(ft_strjoin("PWD=", curpath), env);
	}
	free(tmp);
	return (curpath);
}

char	*cd_dir(t_list *env, char *ar, int p)
{
	char *curpath;

	curpath = ft_strdup(getcwd(NULL, 0));
	curpath = ft_strjoin(curpath, "/");
	curpath = ft_strjoin(curpath, ar);
	//curpath = epur_path(curpath, p);
	if (access(curpath, F_OK) == -1)
		print_cd_err(1, ar);
	else if (check_is_directory(curpath) == -1)
		print_cd_err(2, ar);
	else if (access(curpath, X_OK) == -1)
		print_cd_err(3, ar);
	else
	{
		curpath = epur_path(curpath, p);
		ft_setenv(ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3)), env);
		ft_setenv(ft_strjoin("PWD=", curpath), env);
	}
	return (curpath);
}

char	*cd_double_ar(char **ar, t_list *env, int p)
{
	char *new;
	char *pwd;

	pwd = get_value_env(env, "PWD", 3);
	new = ft_strnew(ft_strlen(pwd) - ft_strlen(ar[1]) + ft_strlen(ar[2]) + 1);
	if (ft_strstr(pwd, ar[1]) != NULL)
	{
		new = strcat(new, ft_strsub(pwd, 0, ft_strlen(pwd) - ft_strlen(ft_strstr(pwd, ar[1]))));
		new = ft_strcat(new, ar[2]);
		new = ft_strcat(new, ft_strstr(pwd, ar[1]) + ft_strlen(ar[1]));
		check_curpath_dble_ar(new , env);
		return (new);
	}
	ft_putstr_fd("cd: string not in pwd: ", 2);
	ft_putendl_fd(ar[1], 2);
	return (NULL);
}
