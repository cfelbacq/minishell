/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 12:36:35 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/16 17:38:26 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		check_unset_ar(char *command)
{
	if (command == NULL)
	{
		ft_putendl_fd("unsetenv: not enough arguments", 2);
		return (0);
	}
	return (1);
}

static	int		check_valid_unset(char *command)
{
	if (check_egal(command) == 1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd("unsetenv ", 2);
		ft_putstr_fd(command, 2);
		ft_putendl_fd(": Invalid argument", 2);
		return (0);
	}
	return (1);
}

static	t_list	*retour(int i, t_list *start_env)
{
	if (i == 0)
		return (start_env);
	else
		return (NULL);
}

void			pre_unsetenv(char **command, t_list **start_env)
{
	int i;

	i = 1;
	if (command[i] == NULL)
		ft_putendl("unsetenv: No arguments");
	while (command[i] != NULL)
	{
		*start_env = ft_unsetenv(command[i], *start_env, 1);
		i++;
	}
}

t_list			*ft_unsetenv(char *command, t_list *start_env, int i)
{
	t_list *tmp;
	t_list *tmp2;

	if (check_unset_ar(command) != 1 || check_valid_unset(command) != 1)
		return (retour(i, start_env));
	tmp = start_env;
	tmp2 = NULL;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, command, len_of_name(tmp->content)) == 0)
		{
			if (tmp2 != NULL)
				tmp2->next = tmp->next;
			free(tmp->content);
			if (tmp2 == NULL)
				start_env = tmp->next;
			free(tmp);
			tmp = NULL;
			return (start_env);
		}
		tmp2 = tmp;
		tmp = tmp->next;
	}
	return (start_env);
}
