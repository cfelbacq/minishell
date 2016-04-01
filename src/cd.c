/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:19:16 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/01 16:02:58 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_directory(t_list *start_env, char **ar)
{
	if (ar[1] == NULL || ft_strcmp(ar[1], "~") == 0)
		chdir(get_value_env(start_env, "HOME", 4));
	else if (len_of_double_tab(ar) == 2)
		chdir(ar[1]);
	else
	{
		if (len_of_double_tab(ar) > 3)
			ft_putendl_fd("cd: too many arguments", 2);
		else
		{
			ft_putstr_fd("cd : string not in pwd: ", 2);
			ft_putendl_fd(ar[2], 2);
		}
	}
}
