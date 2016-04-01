/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 12:28:28 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/01 16:17:20 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_env(t_list *start_env, char *to_find, int size_to_find)
{
	int		i;
	char	**tmp;
	t_list	*tmp_l;

	tmp_l = start_env;
	tmp = NULL;
	i = 0;
	while (tmp_l != NULL)
	{
		if (ft_strncmp(tmp_l->content, to_find, size_to_find) == 0)
		{
			tmp = ft_strsplit(tmp_l->content, '=');
			return (tmp[1]);
		}
		tmp_l = tmp_l->next;
	}
	ft_putstr("value = null");
	return (NULL);
}

int		env(char **command, t_list *start_env)
{
	int i;

	i = 0;
	if (command[1] == NULL)
	{
		print_list(start_env);
		return (1);
	}
	else
	{
		while (command[i] != NULL)
		{
			if (ft_strcmp(command[i], "-i") == 0)
			{
				ft_putendl("nouveau env");
				while (check_egal(command[++i]) == 1)
					start_env = ft_setenv(command[i], start_env);
			}
			if (ft_strcmp(command[i], "-u") == 0)
			{
				if (command[i + 1] == NULL)
				{
					ft_putendl("env: option requires an argument -- u");
					return (1);
				}
				ft_unsetenv(command[i + 1], start_env);
				i++;
			}
			if (check_egal(command[i]) == 1)
				ft_setenv(command[i], start_env);
			i++;
		}
		print_list(start_env);
		return (1);
	}
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
