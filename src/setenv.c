/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:56:22 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/29 15:41:33 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_egal(char *tmp)
{
	int i;

	i = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	len_of_name(char *str)
{
	int i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	return (i);
}

t_list	*ft_setenv(char **command, t_list *start_env)
{
	t_list *tmp;
	char *tmp1;
	t_list *new;
	t_list *previous;

	if (command[1] == NULL)
		return (start_env);
	previous = NULL;
	tmp1 = NULL;
	tmp = start_env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, command[1], len_of_name(command[1])) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strdup(command[1]);
			tmp->content_size = ft_strlen(command[1]) * sizeof(char) + 1;
			if (check_egal(tmp->content) == 0)
				tmp->content = ft_strjoin(tmp->content, "=");
			return (start_env);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	tmp1 = ft_strdup(command[1]);
	if (check_egal(tmp1) == 0)
		tmp1 = ft_strjoin(tmp1, "=");
	previous->next = ft_lstnew(tmp1, ft_strlen(tmp1) + 1);
	return (start_env);
}
