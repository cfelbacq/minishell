/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 12:57:37 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/28 13:21:41 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		interpreteur(char **command, t_list *start_env)
{
	if (command != NULL && ft_strcmp(command[0], "cd") == 0)
	{
		change_directory(start_env, command);
		return (1);
	}
	if (command != NULL && ft_strcmp(command[0], "env") == 0 \
			&& command[1] == NULL)
	{
		print_list(start_env);
		return (1);
	}
	if (command != NULL && ft_strcmp(command[0], "exit") == 0)
		exit(0);
	return (0);
}

void	sys_command(char **path, char **ar)
{
	pid_t pid;
	int i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		while (path[i] != NULL)
		{
			execve(ft_strjoin(path[i], ar[0]), ar, NULL);
			i++;
		}
	}
	else if (pid < 0)
		ft_putstr("fork error");
	else
		wait(&i);
}

void	shell(t_list *start_env, char **path)
{
	char *line;
	char **ar;
	
	ar = NULL;
	line = NULL;
	ft_putstr("$> ");
	while (get_next_line(0, &line))
	{
		ar = ft_strsplit(line, ' ');
		if (interpreteur(ar, start_env) == 0)
			sys_command(path, ar);
		ft_putstr("$> ");
	}
}
