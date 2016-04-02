/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:17:07 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/28 13:18:02 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_list *start)
{
	t_list *tmp;

	tmp = start;
	while (tmp)
	{
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
}

void	put_double_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_putendl(tab[i]);
		i++;
	}
}

int		len_of_double_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

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
