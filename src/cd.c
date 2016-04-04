/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:19:16 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/04 15:42:09 by cfelbacq         ###   ########.fr       */
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

char	**ins_slashes(t_list *start)
{
	t_list *tmp;
	t_list *new;

	ft_putstr(start->content);
	new = NULL;
	tmp = start;
	while (tmp)
	{
		if (ft_strcmp(tmp->content, "/") != 0)
		{
			new = ft_lstnew("/", sizeof(char) + 1);
			new->next = tmp->next;
			tmp->next = new;
			tmp = start;
		}
		tmp = tmp->next;
	}
	return (lst_to_tab(tmp));
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
		ft_putstr(tmp->content);
		if (ft_strcmp(tmp->content, ".") == 0)
		{
			previous->next = tmp->next;
			free(tmp->content);
			free(tmp);
			tmp = new;
			ft_putchar('\n');
		}
		if (ft_strcmp(tmp->content, "..") == 0 && ft_strcmp(previous->content, "/") != 0)
		{
			if (previous_previous != NULL)
			{
				previous_previous->next = tmp->next;
				free(previous->content);
				free(previous);
				free(tmp->content);
				free(tmp);
				tmp = start;
				ft_putstr(new->content);
				ft_putchar('\n');
			}
		}
		if (ft_strcmp(tmp->content, "/") != 0)
			previous_previous = previous;
		previous = tmp;
		tmp = tmp->next;
	}
	return (tmp);
}

char	*epur_path(char *path)
{
	char *tmp;
	char **tmp2;
	int i;
	t_list *path_to_epur;

	i = 0;
	tmp = NULL;
	tmp2 = ft_strsplit(path, '/');
	path_to_epur = init_env(tmp2);
//	free_double_tab(tmp2);
	tmp2 = ins_slashes(epur_list(path_to_epur));
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
			chdir(get_value_env(start_env, "HOME", 4));
		else
			ft_putendl("cd: HOME not set");
	}
	else if (ar[i][0] == '/')
	{
		curpath = ft_strdup(ar[i]);
		ft_putstr(curpath);
	}
	else if (ar[i][0] == '.')
	{
		curpath = ft_strjoin(\
				ft_strjoin(get_value_env(start_env, "PWD", 3), "/"), ar[i]);
		ft_putendl(curpath);
		curpath = epur_path(curpath);
		ft_putendl(curpath);
		curpath = epur_path(curpath);
		chdir(curpath);
	}
	else
	{
		if (access(ar[i], F_OK) == -1)
			ft_putendl("cd: No such file or directory");
		else if (access(ar[i], R_OK) == -1)
			ft_putendl("cd: permission denied");
		else
			chdir(ar[i]);
	}
}
