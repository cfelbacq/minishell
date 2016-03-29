/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 12:36:35 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/29 15:48:49 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_unsetenv(char **command, t_list *start_env)
{
	t_list *tmp;
	t_list *tmp2;

	if (command[1] == NULL)
		return (start_env);
	tmp = start_env;
	tmp2 = NULL;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, command[1], len_of_name(command[1])) == 0)
		{
			if (tmp2 != NULL)
				tmp2->next = tmp->next;
			free(tmp->content);
			if (tmp2 == NULL)
				start_env = tmp->next;
			free(tmp);
			tmp = NULL;
				return (start_env);
		}
		tmp2 = tmp;
		tmp = tmp->next;
	}
	return (start_env);
}
