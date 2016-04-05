/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:56:22 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/05 15:25:13 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*pre_setenv(char **command, t_list *start_env)
{
	int i;

	i = 1;
	if (command[i] == NULL)
		print_list(start_env);
	else
	{
		while (command[i] != NULL)
		{
			if (check_egal(command[i]) == 1)
				start_env = ft_setenv(command[i], start_env);
			else
			{
				ft_putstr("setenv: ");
				ft_putstr(command[i]);
				ft_putendl(": Invalid argument");
			}
			i++;
		}
	}
	return (start_env);
}

t_list	*ft_setenv(char *command, t_list *start_env)
{
	t_list *tmp;
	char *tmp1;
	t_list *new;
	t_list *previous;

	if (start_env == NULL)
	{
		start_env = ft_lstnew(command, ft_strlen(command));
		return (start_env);
	}
	previous = NULL;
	tmp1 = NULL;
	tmp = start_env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, command, len_of_name(command)) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strdup(command);
			tmp->content_size = ft_strlen(command) * sizeof(char) + 1;
			return (start_env);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	tmp1 = ft_strdup(command);
	previous->next = ft_lstnew(tmp1, ft_strlen(tmp1) + 1);
	return (start_env);
}
