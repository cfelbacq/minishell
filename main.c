/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 14:14:38 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/24 15:42:41 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "libft/get_next_line.h"
#include <stdio.h>

char	**split_line(char *line)
{
	char **doubletab;

	doubletab = ft_strsplit(line, ' ');
	return (doubletab);
}

void	free_double(char **tmp)
{
	int i;

	i = 0;
	while (tmp[i] != NULL)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

char	**get_path(char **env)
{
	char **tmp;
	char **path;
	int i;
	int j;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
		{
			tmp = ft_strsplit(env[i], '=');
			path = ft_strsplit(tmp[1], ':');
			free_double(tmp);
		}
		i++;
	}
	return (path);
}

t_list	*get_env(char **env, t_list *start_env)
{
	int i;
	t_list *tmp;

	i = 0;
	start_env = ft_lstnew((char *)env[i], ft_strlen(env[i]) + 1);
	tmp = start_env;
	while (env[++i] != NULL)
	{
		tmp->next = ft_lstnew((char *)env[i], ft_strlen(env[i]) + 1);
		tmp = tmp->next;
	}
	return (start_env);
}

void	print_list(t_list *start)
{
	t_list *tmp;

	tmp = start;
	while (tmp)
	{
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	int i;
	char *line;
	char **ar;
	t_list *start_env;
	t_list *tmp;
	pid_t pid, wpid;
	int status;
	char **path;

	path = get_path(env);
	ar = NULL;
	line = NULL;
	start_env = get_env(env, start_env);
	tmp = start_env;
	i = 0;
	while (1)
	{
		ft_putstr("$> ");
		get_next_line(0, &line);
		ar = split_line(line);
		if (ft_strcmp(ar[0], "cd") == 0)
			chdir(ar[1]);
		if (ft_strcmp(line, "env") == 0)
			print_list(start_env);
		pid = fork();
		if (pid == 0)
		{
			while (path[i] != NULL)
			{
			path[i] = ft_strjoin(path[i], "/");
				execve(ft_strjoin(path[i], ar[0]), ar, NULL);
				i++;
			}
		}
		else if (pid < 0)
			perror("zsh");
		else
			wpid = waitpid(pid, &status, WUNTRACED);
		if (ft_strcmp(line, "exit") == 0)
			exit(0);
	}
	return (0);
}
