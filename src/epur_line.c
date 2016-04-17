/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/17 16:46:17 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/17 16:54:01 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*epur_str(char *to_free, char *str)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = ft_strnew(ft_strlen(str) + 1);
	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			tmp[j] = ' ';
			j++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
		}
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	to_free = str;
	free(to_free);
	return (tmp);
}

char	**check_tild(char **ar, t_list *start_env)
{
	int i;

	i = 0;
	while (ar[i] != NULL)
	{
		if (ft_strcmp(ar[i], "~") == 0)
		{
			ft_strdel(&ar[i]);
			if (check_env_name(start_env, "HOME") == 1)
				ar[i] = ft_strdup(get_value_env(start_env, "HOME", 4));
		}
		i++;
	}
	return (ar);
}
