/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_list_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 17:36:11 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/12 17:48:27 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_list	*free_if_dot(t_list *previous, t_list *tmp, t_list *start)
{
	previous->next = tmp->next;
	free((tmp)->content);
	free(tmp);
	return (start);
}

static	t_list	*free_if_dot_dot(t_list *pre_pre, t_list *pre, t_list *tmp\
		, t_list *start)
{
	pre_pre->next = tmp->next;
	free(pre->content);
	free(pre);
	free(tmp->content);
	free(tmp);
	return (start);
}

int	check_dot(t_list *start)
{
	t_list *tmp;

	tmp = start;
	while (tmp)
	{
		if (ft_strcmp(tmp->content, ".") == 0 || ft_strcmp(tmp->content, "..")\
				== 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

static	t_list	*free_dot_left(t_list *tmp, t_list *pre, t_list *pre_pre,\
		t_list *start)
{
	while (tmp != NULL && (ft_strcmp(tmp->content, "..") == 0 \
				|| ft_strcmp(tmp->content, ".") == 0))
	{
		pre->next = tmp->next;
		pre_pre = tmp;
		free(pre_pre->content);
		free(pre_pre);
		tmp = tmp->next;
	}
	if (check_dot(start) == 0)
		epur_list(start);
	return (start);
}

static	void	for_love_of_norme(t_list **tmp, t_list **pre_pre, t_list **pre)
{
	if (ft_strcmp((*tmp)->content, "/") != 0)
		*pre_pre = *pre;
	*pre = *tmp;
	*tmp = (*tmp)->next;
}

t_list			*epur_list(t_list *start)
{
	t_list	*new;
	t_list	*tmp;
	t_list	*previous;
	t_list	*pre_previous;

	pre_previous = NULL;
	previous = NULL;
	tmp = start;
	while (tmp)
	{
		if (ft_strcmp(tmp->content, ".") == 0)
			tmp = free_if_dot(previous, tmp, start);
		if (ft_strcmp(tmp->content, "..") == 0)
		{
			if (ft_strcmp(previous->content, "/") == 0)
				return (free_dot_left(tmp, previous, pre_previous, start));
			else if (pre_previous != NULL)
				tmp = free_if_dot_dot(pre_previous, previous, tmp, start);
		}
		for_love_of_norme(&tmp, &pre_previous, &previous);
	}
	return (start);
}
