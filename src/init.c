/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:20:21 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/04 11:53:11 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_path(char **path, t_list *env)
{
	int i;

	i = 0;
	path = (ft_strsplit((get_value_env(env, "PATH", ft_strlen("PATH"))), ':'));
	while (path[i] != NULL)
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	return (path);
}

t_list	*init_env(char **env)
{
	t_list	*start;
	t_list	*tmp;
	int		i;

	i = 0;
	start = ft_lstnew(env[i], ft_strlen(env[i]));
	tmp = start;
	while (env[++i] != NULL)
	{
		tmp->next = ft_lstnew(env[i], (ft_strlen(env[i]) + 1));
		tmp = tmp->next;
	}
	return (start);
}
