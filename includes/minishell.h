/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 05:23:15 by jinkim            #+#    #+#             */
/*   Updated: 2020/12/30 04:16:49 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include "../libft/libft.h"

typedef struct	s_lst
{
	char			*name;
	char			*value;
	struct s_lst	*next;
}				t_lst;
t_lst			*g_lstenv;
t_lst			*g_lstexport;

typedef struct	s_global
{
	char		*cmd;
	char		**cmd_argv;
	int			redir_out;
	pid_t		pid;
}				t_global;
t_global		g_global;

/*
** minishell main
*/
char			*front_strtrim(char *str);
char			get_cmd(void);
void			shell_prompt(void);

/*
** redirect
*/
void	redirect(void);

/*
** quote_cmd
*/
void			print_quote(int quote);
char			need_more_cmd(char quote, char *tmp, char *buf);
void			quote_cmd(char quote);

/*
** quote_many_cmd
*/
void			quote_exec_cmd(int	*num1, int *num2, int semi_colon);
void			quote_space(int *num1, int *num2);
void			cmd_argv_malloc(void);
void			quote_many_cmd(int	quote);

/*
** many_cmd
*/
void			free_str_2p(char **str);
void			child_ps(void);
void			exec_cmd(void);
void			many_cmd(void);

/*
** command
*/
void			cmd_cd(void);
void			cmd_exit(void);
void			cmd_env_export(t_lst *lst);

/*
** get lstenv & lstexport
*/
t_lst			*lst_new(char *name, char *value);
t_lst			*lstlast(t_lst *lst);
void			lstadd_back(t_lst **lst, char *name, char *value);
void			init_lst(char **envp);

/*
** lstadd_sort
*/
void			new_curr(t_lst *bef, t_lst *curr, t_lst *new);
void			lst_sort(t_lst *bef, t_lst *curr, t_lst *new, int len);
void			lstadd_sort(t_lst **lst, char *name, char *value);

/*
** env parsing
*/
char			*find_env_value(t_lst *lst, char *name);
char			*get_env_name(char *str);
char			*get_env_value(char *str);

/*
** cmd_export
*/
int				str_equal(char *str);
void			export_not_valid(char *str);
int				str_isalnum(char *str);
void			cmd_export(void);

/*
** edit_lst
*/
void			ch_env_value(t_lst *lst, char *name, char *value);
void			add_lstenv(char *name, char *value);
t_lst			*lst_beforelast(t_lst *lst);
void			add_lstexport(char *name, char *value);
void			edit_lst(char *str);

/*
** cmd_echo
*/
void			echo_env(int idx, int option);
void			cmd_echo(void);

/*
** lst_to_arr
*/
void			copy_lst_cmd(char **env_arr);
char			**lst_to_arr(void);

/*
** cmd_unset
*/
void			lst_delete(t_lst *lst, char *name);
void			unset_invalid(void);
void			cmd_unset(void);

#endif
