/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 12:57:37 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/11 19:31:01 by cfelbacq         ###   ########.fr       */
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
		pre_setenv(command, start_env);
		return (1);
	}
	if (ft_strcmp(command[0], "unsetenv") == 0)
	{
		ft_unsetenv(command[1], *start_env);
		return (1);
	}
	if (ft_strcmp(command[0], "exit") == 0)
	{
		if (command[1] != NULL)
			exit(ft_atoi(command[1]));
		else
			exit(0);
	}
	return (0);
}

void	sys_command(char **path, char **ar, char **env)
{
	pid_t	pid;
	int		i;
	int		err;
	struct sigaction sig;

	/*
	sig.sa_flags = 0;
	sig.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig, NULL);*/
	err = 0;
	i = 0;
	pid = fork();
	if (pid == 0)
	{
		/*
		sig.sa_handler = SIG_DFL;
		sigaction(SIGINT, &sig, NULL);
		ft_putstr("\n\n");*/
		while (path[i] != NULL)
		{
			err = execve(ft_strjoin(path[i], ar[0]), ar, env);
			i++;
		}
		if (err == -1)
			ex_without_path(ar, env);
		exit(0);
	}
	else if (pid < 0)
		ft_putstr("fork_err");
	else
	{
		int status;
		waitpid(pid, &status, 0);
	}
}

char	*epur_str(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = (char *)ft_memalloc(sizeof(char) * ft_strlen(str));
	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			tmp[j++] = ' ';
			while (str[i] == ' ' || str[i] == '\t')
				i++;
		}
		tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

void	shell(char **environ)
{
	char	*line;
	char	**ar;
	t_list	*start_env;
	char	**path;

	ar = NULL;
	line = NULL;
	start_env = init_env(environ);
	prompt(start_env);
	while (get_next_line(0, &line))
	{
		line = ft_strtrim(line);
		line = epur_str(line);
		ar = ft_strsplit(line, ' ');
		if (*ar != NULL && interpreteur(ar, &start_env) == 0)
		{
			path = init_path(path, start_env);
			sys_command(path, ar, lst_to_tab(start_env));
		}
		prompt(start_env);
	}
}
