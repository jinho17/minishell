/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 23:53:29 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/18 14:05:23 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_parent(int **fd, int idx, int pipe_num)
{
	if (idx != 0)
		ft_close(fd[idx - 1][0]);
	if (idx != pipe_num - 1)
		ft_close(fd[idx][1]);
	free_str_2p(g_global.cmd_argv);
}

void	pipe_child(int **fd, int idx, int pipe_num)
{
	if (idx != 0)
	{
		dup2(fd[idx - 1][0], 0);
		ft_close(fd[idx - 1][1]);
		ft_close(fd[idx - 1][0]);
	}
	if (idx != pipe_num - 1)
	{
		dup2(fd[idx][1], 1);
		ft_close(fd[idx][1]);
		ft_close(fd[idx][0]);
	}
	exec_cmd();
	exit(0);
}

void	run_pipe(int **fd, int idx, int pipe_num)
{
	pid_t	pid;

	dollar_change();
	remove_quote();
	remove_empty_str(g_global.cmd_argv, 0);
	path_change(0, 0, find_env_value(g_lstenv, "PATH"));
	pid = fork();
	if (pid == 0)
		pipe_child(fd, idx, pipe_num);
	else if (pid > 0)
		pipe_parent(fd, idx, pipe_num);
	else
		exit(1);
}

int		**malloc_pipefd(int pipe_num)
{
	int		**fd;
	int		idx;

	fd = (int **)malloc(sizeof(int *) * (pipe_num + 1));
	idx = 0;
	while (idx < pipe_num - 1)
	{
		fd[idx] = (int *)malloc(sizeof(int) * 2);
		pipe(fd[idx++]);
	}
	fd[idx] = 0;
	return (fd);
}

void	exec_pipe(char **pipe_cmd)
{
	int		pipe_num;
	int		**fd;
	int		idx;

	pipe_num = 0;
	while (pipe_cmd[pipe_num])
		pipe_num++;
	fd = malloc_pipefd(pipe_num);
	idx = 0;
	while (pipe_cmd[idx])
	{
		g_global.cmd_argv = split_cmd(0, 0, pipe_cmd[idx], ' ');
		run_pipe(fd, idx, pipe_num);
		idx++;
	}
	while (wait(0) > 0)
		;
	idx = 0;
	while (idx < pipe_num - 1)
		free(fd[idx++]);
	free(fd);
}
