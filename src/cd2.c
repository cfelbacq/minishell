/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 17:31:09 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/15 16:35:07 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_slashe(char *ar, t_list *env, int p)
{
	char *curpath;
	char *tmp;
	char *pwd;
	char *oldpwd;

	pwd = NULL;
	oldpwd = NULL;
	curpath = ft_strdup(ar);
	tmp = ft_strdup(curpath);
	if (check_tmp(epur_slashe(tmp), p, ar) != -1)
	{
		curpath = epur_path(curpath, p);
		oldpwd = ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3));
		pwd = ft_strjoin("PWD=", curpath);
		ft_setenv(oldpwd, env);
		ft_setenv(pwd, env);
	}
	return (curpath);
}

char	*epur_slashe(char *tmp)
{
	char	*new;
	int		i;
	int		j;

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
	free(tmp);
	return (new);
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
	ft_putendl(tmp);
	tmp_double = ft_strsplit(tmp, '/');
	new = (char *)ft_memalloc(sizeof(char) * ft_strlen(tmp) + 1);
	while (tmp_double[i] != NULL)
	{
		if (ft_strcmp(new, "/") != 0)
			new = ft_stradd(new, "/");
		new = ft_stradd(new, tmp_double[i]);
		ft_putstr("NEW :");
		ft_putendl(new);
		if (error_check_tmp(tmp, new, tmp_double, ar) == -1)
			return (-1);
		new = epur_path(new, p);
		i++;
	}
	return (0);
}

char	*ft_stradd(char *to_free, char *to_add)
{
	char *tmp;

	tmp = ft_strjoin(to_free, to_add);
	free(to_free);
	return (tmp);
}

char	*cd_dot(t_list *env, char *ar, int p)
{
	char *curpath;
	char *tmp;
	char *oldpwd;
	char *pwd;

	oldpwd = NULL;
	pwd = NULL;
	curpath = NULL;
	curpath = ft_strdup(get_value_env(env, "PWD", 3));
	curpath = ft_stradd(curpath, "/");
	curpath = ft_stradd(curpath, ar);
	tmp = ft_strdup(curpath);
	if (check_tmp(epur_slashe(tmp), p, ar) != -1)
	{
		curpath = epur_path(curpath, p);
		oldpwd = ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3));
		pwd = ft_strjoin("PWD=", curpath);
		ft_setenv(oldpwd, env);
		ft_setenv(pwd, env);
		free(pwd);
		free(oldpwd);
	}
	return (curpath);
}

char	*cd_dir(t_list *env, char *ar, int p)
{
	char *curpath;
	char *pwd;
	char *oldpwd;
	char *tmp;

	pwd = NULL;
	oldpwd = NULL;
	curpath = ft_strdup(getcwd(NULL, 0));
	curpath = ft_stradd(curpath, "/");
	curpath = ft_stradd(curpath, ar);
	tmp = ft_strdup(curpath);
	if (check_tmp(epur_slashe(tmp), p, ar) != -1)
	{
		curpath = epur_path(curpath, p);
		oldpwd = ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3));
		pwd = ft_strjoin("PWD=", curpath);
		ft_setenv(oldpwd, env);
		ft_setenv(pwd, env);
		free(oldpwd);
		free(pwd);
	}
	return (curpath);
}

char	*cd_double_ar(char **ar, t_list *env, int p, int i)
{
	char *new;
	char *pwd;
	char *oldpwd;
	char *tmp;

	pwd = get_value_env(env, "PWD", 3);
	new = ft_strnew(ft_strlen(pwd) - ft_strlen(ar[i]) \
			+ ft_strlen(ar[i + 1]) + 1);
	if (ft_strstr(pwd, ar[i]) != NULL)
	{
		new = ft_strcat(new, ft_strsub(pwd, 0, ft_strlen(pwd) \
					- ft_strlen(ft_strstr(pwd, ar[i]))));
		new = ft_strcat(new, ar[i + 1]);
		new = ft_strcat(new, ft_strstr(pwd, ar[i]) + ft_strlen(ar[i]));
		tmp = ft_strdup(new);
		if (check_tmp(tmp, p, tmp) != -1)
		{
			new = epur_path(new, p);
			pwd = ft_strjoin("PWD=", new);
			oldpwd = ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3));
			ft_setenv(pwd, env);
			ft_setenv(oldpwd, env);
			free(pwd);
			free(oldpwd);
			return (new);
		}
		return (new);
	}
	ft_putstr_fd("cd: string not in pwd: ", 2);
	ft_putendl_fd(ar[i], 2);
	return (NULL);
}
