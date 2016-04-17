/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 12:28:28 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/17 16:39:42 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_after_env(char **tab, int i)
{
	int		size;
	int		j;
	char	**tab2;

	size = 0;
	j = 0;
	tab2 = NULL;
	while (tab[i + size] != NULL)
		size++;
	tab2 = (char **)ft_memalloc(sizeof(char *) * size + 1);
	while (j < size)
	{
		tab2[j] = ft_strdup(tab[i + j]);
		j++;
	}
	tab2[size] = NULL;
	return (tab2);
}

int		env_flags(int *i, char **command, t_list **new_env)
{
	while (command[*i] != NULL && command[*i][0] == '-'\
			&& check_egal(command[*i]) == 0)
	{
		if (ft_strcmp(command[*i], "-i") == 0 \
				|| ft_strcmp(command[*i], "-") == 0)
			env_free(i, new_env);
		else if (ft_strcmp(command[*i], "-u") == 0)
		{
			if (command[*i + 1] == NULL)
			{
				free_lst(*new_env);
				return (u_opt());
			}
			if ((*new_env = ft_unsetenv(command[*i + 1], *new_env, 1)) == NULL)
			{
				free_lst(*new_env);
				return (1);
			}
			*i = *i + 2;
		}
		else
			return (print_env_ill());
	}
	return (0);
}

int		test_access(char *command, char **path)
{
	int		j;
	int		err;
	char	*tmp;

	tmp = NULL;
	err = -1;
	j = 0;
	while (path[j] != NULL)
	{
		tmp = ft_strjoin(path[j], command);
		err = access(tmp, F_OK);
		free(tmp);
		if (err == 0)
			return (err);
		j++;
	}
	err = access((command), F_OK);
	return (err);
}

int		env_ar(char **command, t_list *new_env, int *i, char **path)
{
	char **tab;

	tab = NULL;
	while (command[*i] != NULL && check_egal(command[*i]) == 1)
	{
		if (check_egal(command[*i]) == 1 && char_bef_egal(command[*i]) == 1)
			new_env = ft_setenv(command[*i], new_env);
		*i = *i + 1;
	}
	if (command[*i] == NULL)
		print_list(new_env);
	else
	{
		tab = split_after_env(command, *i);
		if (ft_strcmp(command[*i], "env") == 0)
			env(tab, new_env, path);
		else if (path != NULL && test_access(command[*i], path) == 0)
			sys_command(path, tab, lst_to_tab(new_env));
		else
			print_env_err(command[*i]);
	}
	free_double_tab(tab);
	free_lst(new_env);
	return (1);
}

int		env(char **command, t_list *start_env, char **path)
{
	int		i;
	t_list	*new_env;

	new_env = NULL;
	i = 1;
	if (start_env != NULL)
		new_env = lstdup(start_env);
	if (env_flags(&i, command, &new_env) == 1)
		return (1);
	return (env_ar(command, new_env, &i, path));
}
