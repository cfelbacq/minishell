/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 12:28:49 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/04/14 19:24:58 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <dirent.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

void	pre_unsetenv(char **command, t_list **start_env);
char	*epur_slashe(char *tmp);
int		check_tmp(char *tmp, int p);
void	print_cd_err(int i, char *ar);
t_list	*prompt(t_list *env);
void	ex_without_path(char **ar, char **env);
int		u_opt(void);
void	print_env_err(char *str);
char	*cd_slashe(char *ar, t_list *env, int p);
char	*cd_dot(t_list *env, char *ar, int p);
char	*cd_dir(t_list *env, char *ar, int p);
char	*cd_double_ar(char **ar, t_list *env, int p);
char	*ins_slashes(t_list *start, int p);
char	*epur_path(char *path, int p);
t_list	*epur_list(t_list *start);
void	cd_opt(int *i, int *p, char **ar);
int		check_opt(char *str);
int		check_is_directory(char *curpath);
void	check_curpath_dble_ar(char *curpath, t_list *env);
int		check_env_name(t_list *env, char *name);
t_list	*pre_setenv(char **command, t_list **start_env);
int		interpreteur(char **command, t_list **start_env, char **path);
void	sys_command(char **path, char **ar, char **env);
char	**lst_to_tab(t_list *start_env);
t_list	*lstdup(t_list *to_copy);
int		check_egal(char *tmp);
int		len_of_name(char *str);
t_list	*ft_unsetenv(char *command, t_list *start_env, int i);
t_list	*ft_setenv(char *command, t_list *start_env);
int		env(char **command, t_list *start_env, char **path);
void	print_list(t_list *start);
void	put_double_tab(char **tab);
int		len_of_double_tab(char **tab);
t_list	*init_env(char **env);
char	**init_path(char **path, t_list *env);
void	change_directory(t_list *start_env, char **ar);
void	print_list(t_list *start);
void	shell(char **environ);
char	*get_value_env(t_list *start_env, char *to_find, int size_to_find);
void	free_double_tab(char **tab);
void	free_lst(t_list *lst);

#endif
