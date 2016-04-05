/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 12:57:37 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/05 14:52:13 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		interpreteur(char **command, t_list **start_env)
{
	if (ft_strcmp(command[0], "cd") == 0)
	{
		change_directory(*start_env, command);
		return (1);
	}
	if (ft_strcmp(command[0], "env") == 0)
		return (env(command, *start_env));
	if (ft_strcmp(command[0], "setenv") == 0)
	{
		pre_setenv(command, *start_env);
		return (1);
	}
	if (ft_strcmp(command[0], "unsetenv") == 0)
	{
		ft_unsetenv(command[1], *start_env);
		return (1);
	}
	if (ft_strcmp(command[0], "exit") == 0)
		exit(0);
	return (0);
}

void	sys_command(char **path, char **ar, char **env)
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
			err = execve(ft_strjoin(path[i], ar[0]), ar, env);
			i++;
		}
		if (err == -1)
		{
			ft_putstr("minishell: command not found: ");
			ft_putendl(ar[0]);
		}
		exit(0);
	}
	else if (pid < 0)
		ft_putstr("fork_err");
	else
		wait(&i);
}

void	shell(void)
{
	char	*line;
	char	**ar;
	t_list	*start_env;
	char	**path;

	ar = NULL;
	line = NULL;
	start_env = init_env(environ);
	ft_putstr("$> ");
	while (get_next_line(0, &line))
	{
		line = ft_strtrim(line);
		ar = ft_strsplit(line, ' ');
		if (*ar != NULL && interpreteur(ar, &start_env) == 0)
		{
			path = init_path(path, start_env);
			sys_command(path, ar, lst_to_tab(start_env));
		}
		ft_putstr("$> ");
	}
}
