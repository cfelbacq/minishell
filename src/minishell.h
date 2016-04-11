/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 12:28:49 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/11 13:34:05 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"

extern char **environ;

int		check_env_name(t_list *env, char *name);
t_list	*pre_setenv(char **command, t_list **start_env);
int		interpreteur(char **command, t_list **start_env);
void	sys_command(char **path, char **ar, char **env);
char	**lst_to_tab(t_list *start_env);
t_list	*lstdup(t_list *to_copy);
int		check_egal(char *tmp);
int		len_of_name(char *str);
t_list	*ft_unsetenv(char *command, t_list *start_env);
t_list	*ft_setenv(char *command, t_list *start_env);
int		env(char **command, t_list *start_env);
void	print_list(t_list *start);
void	put_double_tab(char **tab);
int		len_of_double_tab(char **tab);
t_list	*init_env(char **env);
char	**init_path(char **path, t_list *env);
void	change_directory(t_list *start_env, char **ar);
void	print_list(t_list *start);
void	shell(void);
char	*get_value_env(t_list *start_env, char *to_find, int size_to_find);

#endif
