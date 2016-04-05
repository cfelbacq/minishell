/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:19:16 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/05 17:01:27 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_HOME(t_list *env)
{
	t_list *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "HOME", 4) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		check_opt(char *str)
{
	int i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'P' && str[i] != 'L')
			return (0);
		i++;
	}
	return (1);
}

int		len_of_word_l(t_list *start)
{
	int len;
	t_list *tmp;

	tmp = start;
	len = 0;
	while (tmp)
	{
		len = len + ft_strlen(tmp->content) + 1;
		tmp = tmp->next;
	}
	return (len);
}

char	*ins_slashes(t_list *start)
{
	t_list *tmp;
	char *path;

	path = (char *)ft_memalloc(sizeof(char) *len_of_word_l(start));
	tmp = start;
	while (tmp != NULL)
	{
		path = ft_strcat(path, tmp->content);
		if (ft_strcmp(path, "/") != 0 && tmp->next != NULL)
			path = ft_strcat(path, "/");
		tmp = tmp->next;
	}
	return (path);
}

t_list	*epur_list(t_list *start)
{
	t_list *new;
	t_list *tmp;
	t_list	*previous;
	t_list	*previous_previous;

	previous_previous = NULL;
	previous = NULL;
	new = ft_lstnew("/", ft_strlen("/") + 1);
	new->next = start;
	start = new;
	tmp = start;
	while (tmp)
	{
		if (ft_strcmp(tmp->content, ".") == 0)
		{
			previous->next = tmp->next;
			free(tmp->content);
			free(tmp);
			tmp = start;
		}
		if (ft_strcmp(tmp->content, "..") == 0/* && ft_strcmp(previous->content, "/") != 0*/)
		{
			if (previous_previous != NULL)
			{
				previous_previous->next = tmp->next;
				free(previous->content);
				free(previous);
				free(tmp->content);
				free(tmp);
				tmp = start;
			}
			else if (ft_strcmp(previous->content, "/") == 0)
			{
				new->next = NULL;
				return (new);
			}
		}
		if (ft_strcmp(tmp->content, "/") != 0)
			previous_previous = previous;
		previous = tmp;
		tmp = tmp->next;
	}
	return (start);
}

char	*epur_path(char *path)
{
	char *tmp;
	char **tmp2;
	t_list *path_to_epur;

	tmp = NULL;
	tmp2 = ft_strsplit(path, '/');
	path_to_epur = init_env(tmp2);
	path_to_epur = epur_list(path_to_epur);
	tmp = ins_slashes(path_to_epur);
	return (tmp);
}

void	change_directory(t_list *start_env, char **ar)
{
	char	*curpath;
	int		i;
	int		p;
	int j;

	j = 0;
	curpath = NULL;
	i = 1;
	p = 0;
	while (ar[i] != NULL && ar[i][0] == '-')
	{
		j = 0;
		if (check_opt(ar[i]) == 1)
		{
			while (ar[i][j] != '\0')
			{
				if (j >= 1 && ar[i][j] == 'P')
					p = 1;
				else if (j >= 1 && ar[i][j] == 'L')
					p = 0;
				j++;
			}
		}
		i++;
	}
	if (ar[i] == NULL)
	{
		if (check_HOME(start_env) == 1)
		{
			chdir(get_value_env(start_env, "HOME", 4));
			ft_setenv(ft_strjoin("OLDPWD=", get_value_env(start_env, "PWD", 3)), start_env);
			ft_setenv(ft_strjoin("PWD=", get_value_env(start_env, "HOME", 4)), start_env);
			ft_putstr("PWD : ");
			ft_putendl(get_value_env(start_env, "HOME", 4));
		}
		else
			ft_putendl("cd: HOME not set");
	}
	else if (ar[i][0] == '/')
	{
		curpath = ft_strdup(ar[i]);
		chdir(curpath);
		ft_putstr(curpath);
		ft_setenv(ft_strjoin("OLDPWD=", get_value_env(start_env, "PWD", 3)), start_env);
		curpath = ft_strjoin("PWD=", curpath);
		ft_setenv(curpath, start_env);
	}
	else if (ar[i][0] == '.')
	{
		curpath = ft_strjoin(ft_strjoin(get_value_env(start_env, "PWD", 3), "/"), ar[i]);
		curpath = epur_path(curpath);
		ft_putstr("PWD : ");
		ft_putendl(curpath);
		chdir(curpath);
		ft_setenv(ft_strjoin("OLDPWD=", get_value_env(start_env, "PWD", 3)), start_env);
		curpath = ft_strjoin("PWD=", curpath);
		ft_setenv(curpath, start_env);
	}
	else
	{
		if (access(ar[i], F_OK) == -1)
			ft_putendl("cd: No such file or directory");
		else if (access(ar[i], R_OK) == -1)
			ft_putendl("cd: permission denied");
		else
		{
			chdir(ar[i]);
		ar[i] = ft_strjoin(ft_strjoin(get_value_env(start_env, "PWD", 3), "/"), ar[i]);
			ft_setenv(ft_strjoin("OLDPWD=", get_value_env(start_env, "PWD", 3)), start_env);
			ar[i] = ft_strjoin("PWD=", ar[i]);
			ft_putendl(ar[i]);
			ft_setenv(ar[i], start_env);
		}
	}
}
