/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 12:23:34 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/11 13:35:16 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lstdup(t_list *to_copy)
{
	t_list	*new_start;
	t_list	*tmp_new;
	t_list	*tmp_copy;

	new_start = ft_lstnew(to_copy->content, to_copy->content_size);
	tmp_copy = to_copy;
	tmp_copy = tmp_copy->next;
	tmp_new = new_start;
	while (tmp_copy)
	{
		tmp_new->next = ft_lstnew(tmp_copy->content, tmp_copy->content_size);
		tmp_new = tmp_new->next;
		tmp_copy = tmp_copy->next;
	}
	tmp_new = NULL;
	return (new_start);
}

char	**lst_to_tab(t_list *start_env)
{
	int		len;
	t_list	*tmp;
	char	**tab;
	int		i;

	i = 0;
	tab = NULL;
	tmp = start_env;
	len = 0;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	tab = (char **)malloc(sizeof(char *) * len + 1);
	tmp = start_env;
	while (i < len && tmp != NULL)
	{
		tab[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
