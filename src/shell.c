/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 12:57:37 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/14 19:58:27 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		interpreteur(char **command, t_list **start_env, char **path)
{
	if (ft_strcmp(command[0], "cd") == 0)
	{
		change_directory(*start_env, command);
		return (1);
	}
	if (ft_strcmp(command[0], "env") == 0)
		return (env(command, *start_env, path));
	if (ft_strcmp(command[0], "setenv") == 0)
	{
		pre_setenv(command, start_env);
		return (1);
	}
	if (ft_strcmp(command[0], "./minishell") == 0)
		ft_setenv(ft_strjoin("SHLVL=", (ft_itoa(ft_atoi(get_value_env(*start_env, "SHLVL", 5)) + 1))), *start_env);
	if (ft_strcmp(command[0], "unsetenv") == 0)
	{
		pre_unsetenv(command, start_env);
		return (1);
	}
	if (ft_strcmp(command[0], "exit") == 0)
	{
		if (command[1] != NULL)
		{
			free_lst(*start_env);
			exit(ft_atoi(command[1]));
		}
		else
		{
			free_lst(*start_env);
			exit(0);
		}
	}
	return (0);
}

int		check_slashe(char *ar)
{
	int i;

	i = 0;
	while (ar[i] != '\0')
	{
		if (ar[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int		test_path(char **path, char *ar)
{
	int i;
	char *tmp;

	tmp = NULL;
	i = 0;
	while (path[i] != NULL)
	{
		if (check_slashe(ar) == 0)
			tmp = ft_strjoin(path[i], ar);
		else
			tmp = ft_strdup(ar);
		if (access(tmp, F_OK) == 0 && access(tmp, X_OK) == -1)
		{
			ft_putstr("minishell: permission denied: ");
			if (check_slashe(ar) == 0)
				ft_putendl(ar);
			else
				ft_putendl(tmp);
			free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}

void	sys_command(char **path, char **ar, char **env)
{
	pid_t	pid;
	int		i;
	int		err;
	char *tmp;

	tmp = NULL;
	err = 0;
	i = 0;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (path[i] != NULL)
		{
			err = execve(ft_strjoin(path[i], ar[0]), ar, env);
			i++;
		}
		if (err == -1)
		{
			if (test_path(path, ar[0]) == 0)
				ex_without_path(ar, env);
		}
		free_double_tab(path);
		exit(0);
	}
	else if (pid < 0)
		ft_putstr("fork_err");
	else
		waitpid(pid, &i, 0);
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
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char **check_tild(char **ar, t_list *start_env)
{
	int i;

	i = 0;
	while (ar[i] != NULL)
	{
		if (ft_strcmp(ar[i], "~") == 0)
		{
			ft_strdel(&ar[i]);
			if (check_env_name(start_env, "HOME"))
				ar[i] = ft_strdup(get_value_env(start_env, "HOME", 4));
		}
		i++;
	}
	return (ar);
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
	start_env = prompt(start_env);
	path = init_path(path, start_env);
	signal(SIGINT, SIG_IGN);
	while (get_next_line(0, &line))
	{
		line = ft_strtrim(line);
		//line = epur_str(line);
		ar = ft_strsplit(line, ' ');
		free(line);
		ar = check_tild(ar, start_env);
		if (*ar != NULL && interpreteur(ar, &start_env, path) == 0)
			sys_command(path, ar, lst_to_tab(start_env));
		free_double_tab(ar);
		prompt(start_env);
	}
}
