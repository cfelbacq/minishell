/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 12:28:28 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/04 13:29:31 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_env(t_list *start_env, char *to_find, int size_to_find)
{
	int		i;
	char	*tmp;
	t_list	*tmp_l;

	tmp_l = start_env;
	tmp = NULL;
	i = 0;
	while (tmp_l != NULL)
	{
		if (ft_strncmp(tmp_l->content, to_find, size_to_find) == 0)
		{
			tmp = ft_strchr(tmp_l->content, '=');
			return (++tmp);
		}
		tmp_l = tmp_l->next;
	}
	return (NULL);
}


char **split_after_env(char **tab, int i)
{
	int size;
	int j;
	char **tab2;

	size = 0;
	j = 0;
	tab2 = NULL;
	while(tab[i + size] != NULL)
		size++;
	tab2 = (char **)ft_memalloc(sizeof(char *) * size + 1);
	while(j < size)
	{
		tab2[j] = strdup(tab[i + j]);
		j++;
	}
	tab2[size] = NULL;
	return (tab2);
}

static	int	u_opt(void)
{
	ft_putendl("env: option requires an argument -- u");
	return (1);
}

int		env_flags(int *i, char **command, t_list **new_env)
{
	while (command[*i] != NULL && command[*i][0] == '-'\
			&& check_egal(command[*i]) == 0)
	{
		if (ft_strcmp(command[*i], "-i") == 0 \
				|| ft_strcmp(command[*i], "-") == 0)
		{
			*new_env = NULL;
			*i = *i + 1;
		}
		else if (ft_strcmp(command[*i], "-u") == 0)
		{
			if (command[*i + 1] == NULL)
				return (u_opt());
			if (ft_unsetenv(command[*i + 1], *new_env) == NULL)
				return (1);
			*i = *i + 2;
		}
		else
		{
			ft_putendl("env: option illegal");
			break ;
		}
	}
	return (0);
}

int	test_access(char *command, char **path)
{
	int j;
	int err;

	err = 0;
	j = 0;
	while (path[j] != NULL)
	{
		err = access(ft_strjoin(path[j], command), F_OK);
		if (err == 0)
			return (err);
		j++;
	}
	return (err);
}

void	print_env_err(char *str)
{
	ft_putstr("env: ");
	ft_putstr(str);
	ft_putendl(": No such file or directory");
}

int		env_ar(char **command, t_list *new_env, int *i, char **path)
{
	char **env;
	char **tab;

	env = NULL;
	tab = NULL;
	while (command[*i] != NULL && check_egal(command[*i]) == 1)
	{
		new_env = ft_setenv(command[*i], new_env);
		*i = *i + 1;
	}
	if (command[*i] == NULL)
		print_list(new_env);
	else
	{
		env = lst_to_tab(new_env);
		tab = split_after_env(command, *i);
		if (test_access(command[*i], path) == 0)
		{
			if (interpreteur(tab, &new_env) == 0)
				sys_command(path, tab, lst_to_tab(new_env));
		}
		else
			print_env_err(command[*i]);
	}
	return (1);
}

int		env(char **command, t_list *start_env)
{
	int i;
	t_list	*new_env;
	char **path;

	path = init_path(path, start_env);
	i = 1;
	new_env = lstdup(start_env);
	if (env_flags(&i, command, &new_env) == 1)
		return (1);
	return (env_ar(command, new_env, &i, path));
}
