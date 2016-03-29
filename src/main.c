/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 14:14:38 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/28 14:54:57 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

int	main(int argc, char **argv)
{
	char	**path;
	t_list	*start_env;

	start_env = init_env(environ);
	path = init_path(path, start_env);
	shell(start_env, path);
	return (0);
}
