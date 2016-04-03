/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 12:28:28 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/03 14:37:20 by cfelbacq         ###   ########.fr       */
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

int		env(char **command, t_list *start_env)
{
	int i;
	t_list	*new_env;
	char **env;
	char **path;
	char **tab;

	tab = NULL;
	path = init_path(path, start_env);
	env = NULL;
	i = 1;
	new_env = lstdup(start_env);
		while (command[i] != NULL && command[i][0] == '-'\
			&& check_egal(command[i]) == 0)
		{
			if (ft_strcmp(command[i], "-i") == 0)
			{
				new_env = NULL;
				i++;	
			}
			else if (ft_strcmp(command[i], "-u") == 0)
			{
				if (command[i + 1] == NULL)
				{
					ft_putendl("env: option requires an argument -- u");
					return (1);
				}
				ft_unsetenv(command[i + 1], new_env);
				i+= 2;
			}
			else if (ft_strcmp(command[i], "-P") == 0)
			{
				ft_putendl("change_PATH");
				i++;
				ft_putendl(command[i]);
				i++;
			}
			else
			{
				ft_putendl("opt_illegal");
				break ;
			}
		}
		while (command[i] != NULL && check_egal(command[i]) == 1)
		{
			new_env = ft_setenv(command[i], new_env);
			i++;
		}
		if (command[i] == NULL)
			print_list(new_env);
		else
		{
			env = lst_to_tab(new_env);
			tab = split_after_env(command, i);
			if (interpreteur(tab, &new_env) == 0)
				sys_command(path, tab);
		}
		return (1);
/*	else
	{
		while (command[i] != NULL)
		{
			if (check_egal(command[i]) == 1)
				ft_setenv(command[i], start_env);
			else
			{
				if (i != 0)
				{
					ft_putstr("env: ");
					ft_putstr(command[i]);
					ft_putendl(": No such file or directory");
				}
			}
			i++;
		}
		return (1);	
	}*/
	return (0);
}
