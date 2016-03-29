/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 12:57:37 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/29 16:39:43 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		interpreteur(char **command, t_list **start_env)
{
	if (command != NULL && ft_strcmp(command[0], "cd") == 0)
	{
		change_directory(*start_env, command);
		return (1);
	}
	if (command != NULL && ft_strcmp(command[0], "env") == 0)
	{
		if (env(command, *start_env) == 1)
			return (1);
	}
	if (command != NULL && ft_strcmp(command[0], "setenv") == 0)
	{
		*start_env = ft_setenv(command, *start_env);
		return (1);
	}
	if (command != NULL && ft_strcmp(command[0], "unsetenv") == 0)
	{
		*start_env = ft_unsetenv(command, *start_env);
		return (1);
	}
	if (command != NULL && ft_strcmp(command[0], "exit") == 0)
		exit(0);
	return (0);
}

void	sys_command(char **path, char **ar)
{
	pid_t	pid;
	int		i;
	int		err;

	err = 0;
	i = 0;
	pid = fork();
	if (pid == 0)
	{
		while (path[i] != NULL)
		{
				err = execve(ft_strjoin(path[i], ar[0]), ar, NULL);
				i++;
		}
		if (err == -1)
		{
			ft_putstr("zsh: command not found: ");
			ft_putendl(ar[0]);
		}
		exit(0);
	}
	else if (pid < 0)
		ft_putstr("fork_err");
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
		line = ft_strtrim(line);
		ar = ft_strsplit(line, ' ');
		if (interpreteur(ar, &start_env) == 0)
			sys_command(path, ar);
		ft_putstr("$> ");
	}
}
