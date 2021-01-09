/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 05:23:15 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/09 00:39:29 by jinkim           ###   ########.fr       */
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
#include <sys/stat.h>
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
	pid_t		pid;
	char		quote;
	char		cwd[1024];
	int			pipe_num;
	int			pipe;
	int			semi_c;
	int			export_err;
	int			fd_in;
	int			fd_out;
}				t_global;
t_global		g_global;

/*
** minishell main
*/
int				get_cmd(void);
void			shell_prompt(void);

/*
** read_cmd.c
*/
char			*front_strtrim(char *str);
void			print_quote(void);
void			check_condition(char *buf, int space_check);
void			quote_pipe_cond(char *buf, int *space_check);
void			read_cmd(char *buf, int space_check);

/*
** get_cmd_argv.c
*/
int				pipe_check(char *str);
char			**cmd_malloc(void);
void			remove_space(char **cmds);
char			**split_cmd(int num1, int num2, char *str, char trim);
void			get_cmd_argv();

/*
** pipe_version.c
*/
void			remove_empty_str(char **cmds, int idx);
void			move_1char(int num1, int num2);
void			remove_quote(void);
void			no_pipe_version(char **cmds, int idx);
void			pipe_version(char **cmds, int idx);

/*
**	pipe.c
*/
void			dup_close(int *fd, int inout);
void			pipe_parent(int **fd, int idx, int pipe_num);
void			pipe_child(int **fd, int idx, int pipe_num);
void			run_pipe(int **fd, int idx, int pipe_num);
void			exec_pipe(char **pipe_cmd);

/*
** redirect
*/
void			remove_redir(int idx, char **cmds);
void			redir_input(int idx, char **cmds);
void			redir_output(int idx, char **cmds, int double_redir);
int				is_inout(int *idx, char **cmds);
char			**redir_cmds_malloc(void);

/*
** exec_cmd
*/
void			free_str_2p(char **str);
void			parent_ps(void);
void			child_ps(void);
void			exec_cmd(void);

/*
** command
*/
void			pwd_print(void);
void			cmd_exit(void);
void			cmd_cd(void);
void			cmd_env_export(t_lst *lst);

/*
** cmd_bin
*/
void			cmd_echo_bin(void);
void			cmd_bin(void);

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
** dollar change
*/
char			*change_value(int idx, int num, int *len, char *value);
int				get_len(int idx, int len);
int				dollar_value(int idx, int num);
void			dollar_change(void);

/*
** cmd_export
*/
int				str_equal(char *str);
void			export_not_valid(char *str);
int				export_isalnum(char *str);
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
** lst_to_arr
*/
void			copy_lst_cmd(char **env_arr);
char			**lst_to_arr(void);

/*
** cmd_unset
*/
void			lst_delete(t_lst *lst, char *name);
void			unset_invalid(void);
int				unset_isalnum(char *str);
void			run_unset(void);
void			cmd_unset(void);

/*
** change_path
*/
void			change_path(void);

#endif
