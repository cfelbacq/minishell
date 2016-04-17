/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_double_ar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/17 15:53:26 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/17 16:32:55 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	*print_cd_double_ad_err(char *ar, char *new)
{
	ft_putstr_fd("cd: string not in pwd: ", 2);
	ft_putendl_fd(ar, 2);
	free(new);
	return (NULL);
}

static	char	*cat_new(char *new, char **v_pwd, char **ar, t_two_int integer)
{
	char *tmp;

	tmp = ft_strsub(*v_pwd, 0, ft_strlen(*v_pwd) -\
			ft_strlen(ft_strstr(*v_pwd, ar[integer.i])));
	new = ft_strcat(new, tmp);
	free(tmp);
	new = ft_strcat(new, ar[integer.i + 1]);
	new = ft_strcat(new, ft_strstr(*v_pwd, ar[integer.i]) +\
			ft_strlen(ar[integer.i]));
	return (new);
}

static	void	free_cd_double_ar(char **v_pwd, char *tmp, char *oldpwd)
{
	free(*v_pwd);
	free(tmp);
	free(oldpwd);
}

char			*cd_double_ar(char **ar, t_list **env, t_two_int integer,\
		char **v_pwd)
{
	char *new;
	char *oldpwd;
	char *tmp;

	new = ft_strnew(ft_strlen(*v_pwd) - ft_strlen(ar[integer.i]) \
			+ ft_strlen(ar[integer.i + 1]) + 1);
	if (ft_strstr(*v_pwd, ar[integer.i]) != NULL)
	{
		new = cat_new(new, v_pwd, ar, integer);
		tmp = ft_strdup(new);
		if (check_tmp(tmp, integer.p, tmp) != -1)
		{
			free(tmp);
			new = epur_path(new, integer.p);
			oldpwd = ft_strjoin("OLDPWD=", *v_pwd);
			*env = ft_setenv(oldpwd, *env);
			tmp = ft_strjoin("PWD=", new);
			*env = ft_setenv(tmp, *env);
			free_cd_double_ar(v_pwd, tmp, oldpwd);
			*v_pwd = ft_strdup(new);
		}
		return (new);
	}
	return (print_cd_double_ad_err(ar[integer.i], new));
}
