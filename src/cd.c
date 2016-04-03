/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:19:16 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/03 17:11:36 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_HOME(t_list *env)
{
	t_list *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "HOME", 4) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		check_opt(char *str)
{
	int i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'P' && str[i] != 'L')
			return (0);
		i++;
	}
	return (1);
}

void	change_directory(t_list *start_env, char **ar)
{
	char	*home;
	char	*curpath;
	int		i;
	int		p;
	int j;

	j = 0;
	home = NULL;
	curpath = NULL;
	i = 1;
	p = 0;
	while (ar[i] != NULL && ar[i][0] == '-')
	{
		j = 0;
		if (check_opt(ar[i]) == 1)
		{
			while (ar[i][j] != '\0')
			{
				if (j > 1 && ar[i][j] == 'P')
					p = 1;
				else if (j > 1 && ar[i][j] == 'L')
					p = 0;
				j++;
			}
		}
		i++;
	}
	ft_putnbr(p);
	if (ar[i] == NULL)
	{
		if (check_HOME(start_env) == 1)
			chdir(get_value_env(start_env, "HOME", 4));
		else
			ft_putendl("cd: HOME not set");
	}
	else
		
}
