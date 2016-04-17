/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 17:31:09 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/17 16:00:55 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
