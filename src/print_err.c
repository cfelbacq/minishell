/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 18:32:48 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/11 18:40:37 by cfelbacq         ###   ########.fr       */
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
	return (1);
}

void	print_env_err(char *str)
{
	ft_putstr("env: ");
	ft_putstr(str);
	ft_putendl(": No such file or directory");
}
