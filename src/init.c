/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:20:21 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/17 15:41:04 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_path(char **path, t_list *env)
{
	int i;

	i = 0;
	if (check_env_name(env, "PATH") == 0)
		return (NULL);
	path = (ft_strsplit((get_value_env(env, "PATH", ft_strlen("PATH"))), ':'));
	while (path[i] != NULL)
	{
		path[i] = ft_stradd(path[i], "/");
		i++;
	}
	return (path);
}

t_list	*init_env(char **env)
{
	t_list	*start;
	t_list	*tmp;
	int		i;

	if (*env == NULL)
	{
		start = NULL;
		return (start);
	}
	i = 0;
	start = ft_lstnew(env[i], sizeof(char) * ft_strlen(env[i]));
	tmp = start;
	while (env[++i] != NULL)
	{
		tmp->next = ft_lstnew(env[i], (sizeof(char) * ft_strlen(env[i]) + 1));
		tmp = tmp->next;
	}
	return (start);
}

char	*init_pwd(char *pwd)
{
	char *tmp;

	tmp = getcwd(NULL, 0);
	pwd = ft_strdup(tmp);
	free(tmp);
	return (pwd);
}
