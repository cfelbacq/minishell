/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 17:31:09 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/16 20:07:04 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_slashe(char *ar, t_list **env, int p, char **v_pwd)
{
	char *curpath;
	char *tmp;
	char *oldpwd;

	oldpwd = NULL;
	curpath = ft_strdup(ar);
	tmp = ft_strdup(curpath);
	tmp = epur_slashe(tmp);
	if (check_tmp(tmp, p, ar) != -1)
	{
		free(tmp);
		curpath = epur_path(curpath, p);
		oldpwd = ft_strjoin("OLDPWD=", *v_pwd);
		tmp = ft_strjoin("PWD=", curpath);
		*env = ft_setenv(oldpwd, *env);
		*env = ft_setenv(tmp, *env);
		free(*v_pwd);
		*v_pwd = ft_strdup(curpath);
		free(oldpwd);
		free(tmp);
	}
	return (curpath);
}

char	*epur_slashe(char *tmp)
{
	char	*new;
	int		i;
	int		j;

	j = 0;
	new = ft_strnew(sizeof(char) * ft_strlen(tmp) + 1);
	i = 0;
	while (tmp[i] != '\0')
	{
		if (!(tmp[i] == '/' && tmp[i + 1] == '/'))
		{
			new[j] = tmp[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	free(tmp);
	return (new);
}

char	*cd_dot(t_list **env, char *ar, int p, char **v_pwd)
{
	char *curpath;
	char *tmp;
	char *oldpwd;

	oldpwd = NULL;
	curpath = NULL;
	curpath = ft_strdup(*v_pwd);
	curpath = ft_stradd(curpath, "/");
	curpath = ft_stradd(curpath, ar);
	tmp = ft_strdup(curpath);
	tmp = epur_slashe(tmp);
	if (check_tmp(tmp, p, ar) != -1)
	{
		free(tmp);
		curpath = epur_path(curpath, p);
		oldpwd = ft_strjoin("OLDPWD=", *v_pwd);
		tmp = ft_strjoin("PWD=", curpath);
		*env = ft_setenv(oldpwd, *env);
		*env = ft_setenv(tmp, *env);
		free(*v_pwd);
		*v_pwd = ft_strdup(curpath);
		free(tmp);
		free(oldpwd);
	}
	return (curpath);
}

char	*cd_dir(t_list **env, char *ar, int p, char **v_pwd)
{
	char *curpath;
	char *oldpwd;
	char *tmp;

	oldpwd = NULL;
	curpath = ft_strdup(*v_pwd);
	curpath = ft_stradd(curpath, "/");
	curpath = ft_stradd(curpath, ar);
	tmp = ft_strdup(curpath);
	tmp = epur_slashe(tmp);
	if (check_tmp(tmp, p, ar) != -1)
	{
		free(tmp);
		curpath = epur_path(curpath, p);
		oldpwd = ft_strjoin("OLDPWD=", *v_pwd);
		tmp = ft_strjoin("PWD=", curpath);
		*env = ft_setenv(oldpwd, *env);
		*env = ft_setenv(tmp, *env);
		free(*v_pwd);
		*v_pwd = ft_strdup(curpath);
		free(oldpwd);
		free(tmp);
	}
	return (curpath);
}

char	*print_cd_double_ad_err(char *ar, char *new)
{
	ft_putstr_fd("cd: string not in pwd: ", 2);
	ft_putendl_fd(ar, 2);
	free(new);
	return (NULL);
}

char	*cd_double_ar(char **ar, t_list **env, int p, int i, char **v_pwd)
{
	char *new;
	char *oldpwd;
	char *tmp;

	new = ft_strnew(ft_strlen(*v_pwd) - ft_strlen(ar[i]) \
			+ ft_strlen(ar[i + 1]) + 1);
	if (ft_strstr(*v_pwd, ar[i]) != NULL)
	{
		new = ft_strcat(new, ft_strsub(*v_pwd, 0, ft_strlen(*v_pwd) \
					- ft_strlen(ft_strstr(*v_pwd, ar[i]))));
		new = ft_strcat(new, ar[i + 1]);
		new = ft_strcat(new, ft_strstr(*v_pwd, ar[i]) + ft_strlen(ar[i]));
		tmp = ft_strdup(new);
		if (check_tmp(tmp, p, tmp) != -1)
		{
			free(tmp);
			new = epur_path(new, p);
			oldpwd = ft_strjoin("OLDPWD=", *v_pwd);
			*env = ft_setenv(oldpwd, *env);
			tmp = ft_strjoin("PWD=", new);
			*env = ft_setenv(tmp, *env);
			free(tmp);
			free(oldpwd);
			free(*v_pwd);
			*v_pwd = ft_strdup(new);
			return (new);
		}
		return (new);
	}
	return (print_cd_double_ad_err(ar[i], new));
}
