/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 15:25:06 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/16 12:48:40 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_tab(char **tab)
{
	int i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i] != NULL)
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	free_lst(t_list *lst)
{
	t_list *tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		free(tmp->content);
		free(tmp);
		tmp = tmp->next;
	}
}
