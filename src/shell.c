/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 12:57:37 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/17 17:02:10 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		interpreter(char **command, t_list **start_env, char **path,\
		char **pwd)
{
	if (ft_strcmp(command[0], "cd") == 0)
	{
		change_directory(start_env, command, pwd);
		return (1);
	}
	if (ft_strcmp(command[0], "env") == 0)
		return (env(command, *start_env, path));
	if (ft_strcmp(command[0], "setenv") == 0)
	{
		pre_setenv(command, start_env);
		return (1);
	}
	if (ft_strcmp(command[0], "unsetenv") == 0)
	{
		pre_unsetenv(command, start_env);
		return (1);
	}
	if (ft_strcmp(command[0], "exit") == 0)
		return (ft_exit(command, *start_env, path, *pwd));
	return (0);
}

void	child_process(char **path, char **ar, char **env)
{
	int		i;
	int		err;
	char	*tmp;

	tmp = NULL;
	err = 0;
	i = 0;
	signal(SIGINT, SIG_DFL);
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], ar[0]);
		err = execve(tmp, ar, env);
		free(tmp);
		i++;
	}
	if (err == -1)
	{
		if (test_path(path, ar[0]) == 0)
			ex_without_path(ar, env);
	}
	free_double_tab(ar);
	free_double_tab(env);
	free_double_tab(path);
	exit(0);
}

void	sys_command(char **path, char **ar, char **env)
{
	pid_t	pid;
	int		i;

	i = 0;
	pid = fork();
	if (pid == 0)
		child_process(path, ar, env);
	else if (pid < 0)
		ft_putstr("fork_err");
	else
	{
		free_double_tab(env);
		waitpid(pid, &i, 0);
	}
}

void	shell(char **environ)
{
	char	*line;
	char	**ar;
	t_list	*start_env;
	char	*tmp;
	t_env	var;

	line = NULL;
	start_env = init_env(environ);
	var.path = init_path(var.path, start_env);
	var.pwd = init_pwd(var.pwd);
	prompt(var.pwd);
	while (get_next_line(0, &line))
	{
		tmp = line;
		line = ft_strtrim(line);
		free(tmp);
		line = epur_str(tmp, line);
		ar = ft_strsplit(line, ' ');
		free(line);
		ar = check_tild(ar, start_env);
		if (*ar != NULL && interpreter(ar, &start_env, var.path, &var.pwd) == 0)
			sys_command(var.path, ar, lst_to_tab(start_env));
		free_double_tab(ar);
		prompt(var.pwd);
	}
}
