/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:19:16 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/11 15:56:37 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void	check_curpath(char *curpath, t_list *env);

int		check_env_name(t_list *env, char *name)
{
	t_list *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, name, ft_strlen(name)) == 0)
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

char	*r_link(char *path, char *str_to_check)
{
	struct stat buf;
	char *link_name;
	int r;

	r = 0;
	link_name = NULL;
	lstat(ft_strjoin(path, str_to_check), &buf);
	if ((buf.st_mode & S_IFMT)  == S_IFLNK)
	{
		link_name = (char *)ft_memalloc(sizeof(char) * buf.st_size + 1);
		r = readlink(ft_strjoin(path, str_to_check), link_name, buf.st_size);
		link_name[r] = '\0';
		free(str_to_check);
		return (link_name);
	}
	return (str_to_check);
}

char	*ins_slashes(t_list *start, int p)
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
		if (tmp->next != NULL && p == 1)
			(tmp->next)->content = r_link(path, (tmp->next)->content);
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
			if (ft_strcmp(previous->content, "/") == 0)//&& (tmp->next == NULL || ft_strcmp("..", (tmp->next)->content) != 0))
			{
				while (tmp != NULL && (ft_strcmp(tmp->content, "..") == 0 || ft_strcmp(tmp->content, ".") == 0))
				{
					ft_putendl(tmp->content);
					previous->next = tmp->next;
					previous_previous = tmp;
					free(previous_previous);
					tmp = tmp->next;
				}
				return (new);
			}
			else if (previous_previous != NULL)
			{
				previous_previous->next = tmp->next;
				free(previous->content);
				free(previous);
				free(tmp->content);
				free(tmp);
				tmp = start;
			}
		}
		if (ft_strcmp(tmp->content, "/") != 0)
			previous_previous = previous;
		previous = tmp;
		tmp = tmp->next;
	}
	return (start);
}

char	*epur_path(char *path, int p)
{
	char	*tmp;
	char	**tmp2;
	t_list	*path_to_epur;

	tmp = NULL;
	tmp2 = ft_strsplit(path, '/');
	path_to_epur = init_env(tmp2);
	path_to_epur = epur_list(path_to_epur);
	tmp = ins_slashes(path_to_epur, p);
	return (tmp);
}

void	cd_opt(int *i, int *p, char **ar)
{
	int j;

	j = 0;
	while (ar[*i] != NULL && ar[*i][0] == '-')
	{
		j = 0;
		if (check_opt(ar[*i]) == 1)
		{
			while (ar[*i][j] != '\0')
			{
				if (j >= 1 && ar[*i][j] == 'P')
					*p = 1;
				else if (j >= 1 && ar[*i][j] == 'L')
					*p = 0;
				j++;
			}
			*i = *i + 1;
		}
		else
		{
			p = 0;
			return ;
		}
	}
	return ;
}

void	cd_dash(t_list *env)
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
		ft_putendl("cd: OLDPWD not set");
}

void	cd_home(t_list *env)
{
	if (check_env_name(env, "HOME") == 1)
	{
		chdir(get_value_env(env, "HOME", 4));
		ft_setenv(ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3)), env);
		ft_setenv(ft_strjoin("PWD=", get_value_env(env, "HOME", 4)), env);
		ft_putstr("PWD : ");
		ft_putendl(get_value_env(env, "HOME", 4));
	}
	else
		ft_putendl("cd: HOME not set");
}

int		check_is_directory(char *curpath)
{
	struct stat buf;

	lstat(curpath, &buf);
	if ((buf.st_mode & S_IFMT) == S_IFDIR \
			|| ((buf.st_mode & S_IFMT) == S_IFLNK && opendir(curpath) != NULL))
		return (0);
	else
		return (-1);
}

char	*cd_slashe(char *ar, t_list *env, int p)
{
	char *curpath;

	curpath = ft_strdup(ar);
	ft_putendl(curpath);
	if (access(curpath, F_OK) == -1)
	{
		ft_putstr("cd: No suck file or directory: ");
		ft_putendl(ar);
	}
	else if (check_is_directory(curpath) == -1)
	{
		ft_putstr("cd: Not a directory: ");
		ft_putendl(ar);
	}
	else if (access(curpath, R_OK) == -1)
	{
		ft_putstr("cd: Permission denied: ");
		ft_putendl(ar);
	}
	else
	{
		curpath = epur_path(curpath, p);
		ft_putstr("PATH EPUR : ");
		ft_putendl(curpath);
		ft_setenv(ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3)), env);
		ft_setenv(ft_strjoin("PWD=", curpath), env);
	}
	return (curpath);
}

char	*cd_dot(t_list *env, char *ar, int p)
{
	char *curpath;

	curpath = NULL;
	curpath = ft_strjoin(ft_strjoin(get_value_env(env, "PWD", 3), "/"), ar);
	ft_putendl(curpath);
	if (access(curpath, F_OK) == -1)
	{
		ft_putstr("cd: No suck file or directory: ");
		ft_putendl(ar);
	}
	else if (check_is_directory(curpath) == -1)
	{
		ft_putstr("cd: Not a directory: ");
		ft_putendl(ar);
	}
	else if (access(curpath, R_OK) == -1)
	{
		ft_putstr("cd: Permission denied: ");
		ft_putendl(ar);
	}
	else
	{
		curpath = epur_path(curpath, p);
		ft_putstr("PATH EPUR : ");
		ft_putendl(curpath);
		ft_setenv(ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3)), env);
		ft_setenv(ft_strjoin("PWD=", curpath), env);
	}
	return (curpath);
}

char	*cd_dir(t_list *env, char *ar, int p)
{
	char *curpath;

	curpath = ft_strdup(get_value_env(env, "PWD", 3));
	curpath = ft_strjoin(curpath, "/");
	curpath = ft_strjoin(curpath, ar);
	ft_putendl(curpath);
	if (access(curpath, F_OK) == -1)
	{
		ft_putstr("cd: No suck file or directory: ");
		ft_putendl(ar);
	}
	else if (check_is_directory(curpath) == -1)
	{
		ft_putstr("cd: Not a directory: ");
		ft_putendl(ar);
	}
	else if (access(curpath, R_OK) == -1)
	{
		ft_putstr("cd: Permission denied: ");
		ft_putendl(ar);
	}
	else
	{
		curpath = epur_path(curpath, p);
		ft_putstr("PATH EPUR : ");
		ft_putendl(curpath);
		ft_setenv(ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3)), env);
		ft_setenv(ft_strjoin("PWD=", curpath), env);
	}
	return (curpath);
}

char	*cd_double_ar(char **ar, t_list *env, int p)
{
	char **tmp;
	t_list *tmp2;

	tmp2 = NULL;
	tmp = ft_strsplit(get_value_env(env, "PWD", 3), '/');
	int i;
	
	i = 0;
	while (tmp[i] != NULL)
	{
		if (ft_strcmp(tmp[i], ar[1]) == 0)
		{
			free(tmp[i]);
			tmp[i] = ft_strdup(ar[2]);
			tmp2 = init_env(tmp);
			tmp2 = epur_list(tmp2);
			print_list(tmp2);
			check_curpath(ins_slashes(tmp2, p), env);
			return (ins_slashes(tmp2, p));
		}
		i++;
	}
	ft_putstr("cd: string not in pwd: ");
	ft_putendl(ar[1]);
	return (NULL);
}

void	check_curpath(char *curpath, t_list *env)
{
	if (access(curpath, F_OK) == -1)
	{
		ft_putstr("cd: No suck file or directory: ");
		ft_putendl(curpath);
	}
	else if (check_is_directory(curpath) == -1)
	{
		ft_putstr("cd: Not a directory: ");
		ft_putendl(curpath);
	}
	else if (access(curpath, R_OK) == -1)
	{
		ft_putstr("cd: Permission denied: ");
		ft_putendl(curpath);
	}
	else
	{
		ft_setenv(ft_strjoin("OLDPWD=", get_value_env(env, "PWD", 3)), env);
		ft_setenv(ft_strjoin("PWD=", curpath), env);
	}
}

void	change_directory(t_list *start_env, char **ar)
{
	char	*curpath;
	int		i;
	int		p;

	curpath = NULL;
	i = 1;
	p = 0;
	cd_opt(&i, &p, ar);
	if (len_of_double_tab(ar) - i > 2)
		ft_putendl("cd: too many arguments");
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
	ft_putstr("CD : ");
	if (curpath != NULL)
		ft_putendl(curpath);
	chdir(curpath);
}
