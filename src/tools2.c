/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 12:23:34 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/16 14:27:56 by cfelbacq         ###   ########.fr       */
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

char	*get_value_env(t_list *start_env, char *to_find, int size_to_find)
{
	int		i;
	char	*tmp;
	t_list	*tmp_l;

	tmp_l = start_env;
	tmp = NULL;
	i = 0;
	while (tmp_l != NULL)
	{
		if (ft_strncmp(tmp_l->content, to_find, size_to_find) == 0)
		{
			tmp = ft_strchr(tmp_l->content, '=');
			return (++tmp);
		}
		tmp_l = tmp_l->next;
	}
	return (NULL);
}

int		check_env_name(t_list *env, char *name)
{
	t_list *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, name, ft_strlen(name)) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*ft_stradd(char *to_free, char *to_add)
{
	char *tmp;

	tmp = ft_strjoin(to_free, to_add);
	free(to_free);
	return (tmp);
}
