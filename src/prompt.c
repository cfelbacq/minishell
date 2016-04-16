/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 18:34:54 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/16 14:41:06 by cfelbacq         ###   ########.fr       */
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

void			prompt(char *pwd)
{
	ft_putstr("$> ");
	last_word_after_c('/', pwd);
	ft_putstr(": ");
}
