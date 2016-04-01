/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 12:36:35 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/01 13:31:11 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_unsetenv(char *command, t_list *start_env)
{
	t_list *tmp;
	t_list *tmp2;

	if (command == NULL)
		return (start_env);
	if (check_egal(command) == 1)
	{
		ft_putstr("env: ");
		ft_putstr("unsetenv ");
		ft_putstr(command);
		ft_putendl(": Invalid argument");
	}
	tmp = start_env;
	tmp2 = NULL;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, command, len_of_name(command)) == 0)
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
