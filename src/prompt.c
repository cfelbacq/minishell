/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 18:34:54 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/15 12:31:09 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*last_word_after_c(char c, char *str)
{
	int i;

	i = ft_strlen(str);
	while (str[i] != c && i >= 0)
		i--;
	if (i >= 0)
	{
		if (i == 0)
			ft_putchar(str[i]);
		while (str[i++] != '\0')
			ft_putchar(str[i]);
	}
	return (NULL);
}

t_list			*prompt(t_list *env)
{
	//VOIR SETENV a l 'appel de env -i ./minishell
	//if (check_env_name(env, "PWD") == 0)
	//	env = ft_setenv(ft_strjoin("PWD=", getcwd(NULL, 0)), env);
	ft_putstr("$> ");
	if (check_env_name(env, "PWD") == 1)
		last_word_after_c('/', get_value_env(env, "PWD", 3));
	else
		last_word_after_c('/', getcwd(NULL, 0));
	ft_putstr(": ");
	return (env);
}
