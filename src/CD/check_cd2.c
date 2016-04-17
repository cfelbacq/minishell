/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/17 16:20:46 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/17 16:21:42 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
