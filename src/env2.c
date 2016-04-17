/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/17 16:36:19 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/17 16:36:59 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_env_ill(void)
{
	ft_putendl_fd("env: illegal option", 2);
	return (1);
}

void	env_free(int *i, t_list **new_env)
{
	free_lst(*new_env);
	*new_env = NULL;
	*i = *i + 1;
}
