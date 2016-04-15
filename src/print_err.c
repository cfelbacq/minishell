/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 18:32:48 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/15 16:30:20 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_without_path(char **ar, char **env)
{
	if (execve(ar[0], ar, env) == -1)
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(ar[0]);
	}
}

int		u_opt(void)
{
	ft_putendl("env: option requires an argument -- u");
	ft_putstr("usage: env [-i] [-u name] [name=value ...]");
	ft_putendl(" [utility [argument ...]]");
	return (1);
}

void	print_env_err(char *str)
{
	ft_putstr("env: ");
	ft_putstr(str);
	ft_putendl(": No such file or directory");
}

void	print_cd_err(int i, char *ar)
{
	if (i == 1)
	{
		ft_putstr_fd("cd: No such file or directory: ", 2);
		ft_putendl_fd(ar, 2);
	}
	if (i == 2)
	{
		ft_putstr_fd("cd: Not a directory: ", 2);
		ft_putendl_fd(ar, 2);
	}
	if (i == 3)
	{
		ft_putstr_fd("cd: Permission denied: ", 2);
		ft_putendl_fd(ar, 2);
	}
}
