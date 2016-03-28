/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 12:28:28 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/28 13:22:50 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_elem_env(t_list *start_env, char *to_find, int size_to_find)
{
	int i;
	char **tmp;
	t_list *tmp_l;

	tmp_l = start_env;
	tmp = NULL;
	i = 0;
	while (tmp_l != NULL)
	{
		if (ft_strncmp(tmp_l->content, to_find, size_to_find) == 0)
		{
			tmp = ft_strsplit(tmp_l->content, '=');
			return (tmp[1]);
		}
		tmp_l = tmp_l->next;
	}
	return (NULL);
}
