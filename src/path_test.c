/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/17 16:25:51 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/17 16:26:34 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_slashe(char *ar)
{
	int i;

	i = 0;
	while (ar[i] != '\0')
	{
		if (ar[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int		test_path(char **path, char *ar)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (path[i] != NULL)
	{
		if (check_slashe(ar) == 0)
			tmp = ft_strjoin(path[i], ar);
		else
			tmp = ft_strdup(ar);
		if (access(tmp, F_OK) == 0 && access(tmp, X_OK) == -1)
		{
			ft_putstr("minishell: permission denied: ");
			if (check_slashe(ar) == 0)
				ft_putendl(ar);
			else
				ft_putendl(tmp);
			free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}
