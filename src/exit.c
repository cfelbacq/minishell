/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/17 16:24:07 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/17 16:24:30 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exit(char **command, t_list *start_env, char **path, char *pwd)
{
	int i;

	i = 0;
	if (command[1] != NULL && command[2] == NULL)
	{
		free_lst(start_env);
		free_double_tab(path);
		i = ft_atoi(command[1]);
		free_double_tab(command);
		free(pwd);
		exit(i);
	}
	else if (command[1] == NULL)
	{
		free_lst(start_env);
		free_double_tab(path);
		free_double_tab(command);
		free(pwd);
		exit(0);
	}
	else if (command[2] != NULL)
		ft_putendl("exit: too many arguments");
	return (1);
}
