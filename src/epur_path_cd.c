/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_path_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 17:26:37 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/16 19:08:30 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		len_of_word_l(t_list *start)
{
	int		len;
	t_list	*tmp;

	tmp = start;
	len = 0;
	while (tmp)
	{
		len = len + ft_strlen(tmp->content) + 1;
		tmp = tmp->next;
	}
	return (len);
}

char	*r_link(char *path, char *str_to_check)
{
	struct stat	buf;
	char		*link_name;
	int			r;
	char		*tmp;

	tmp = ft_strjoin(path, str_to_check);
	r = 0;
	link_name = NULL;
	lstat(tmp, &buf);
	free(tmp);
	if ((buf.st_mode & S_IFMT) == S_IFLNK)
	{
		link_name = (char *)ft_memalloc(sizeof(char) * buf.st_size + 1);
		r = readlink(ft_strjoin(path, str_to_check), link_name, buf.st_size);
		link_name[r] = '\0';
		free(str_to_check);
		return (link_name);
	}
	return (str_to_check);
}

char	*ins_slashes(t_list *start, int p)
{
	t_list	*tmp;
	char	*path;
	int		i;

	i = 0;
	path = ft_strnew(sizeof(char) * len_of_word_l(start));
	//path = (char *)ft_memalloc(sizeof(char) * len_of_word_l(start));
	tmp = start;
	while (tmp != NULL)
	{
		path = ft_stradd(path, tmp->content);
		if (ft_strcmp(path, "/") != 0 && tmp->next != NULL)
			path = ft_stradd(path, "/");
		if (tmp->next != NULL && p == 1)
			(tmp->next)->content = r_link(path, (tmp->next)->content);
		tmp = tmp->next;
		i++;
	}
	return (path);
}

char	*epur_path(char *path, int p)
{
	char	*tmp;
	char	**tmp2;
	t_list	*path_to_epur;
	t_list	*new;

	path_to_epur = NULL;
	tmp = NULL;
	tmp2 = ft_strsplit(path, '/');
	if (tmp2 != NULL)
	{
		path_to_epur = init_env(tmp2);
		free_double_tab(tmp2);
	}
	new = ft_lstnew("/", ft_strlen("/") + 1);
	new->next = path_to_epur;
	path_to_epur = new;
	path_to_epur = epur_list(path_to_epur);
	tmp = ins_slashes(path_to_epur, p);
	free_lst(path_to_epur);
	free(path);
//	free_lst(path_to_epur);
	return (tmp);
}
