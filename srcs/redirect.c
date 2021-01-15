/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 02:16:27 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/12 19:42:06 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		child_ps();
	else if (pid > 0)
		wait(0);
	else
		exit(1);
}

void	malloc_fd(void)
{
	int	idx;

	idx = 0;
	while (g_global.cmd_argv[idx])
		idx++;
	g_global.fd = (int **)malloc(sizeof(int *) * 2);
	g_global.fd[0] = (int *)malloc(sizeof(int) * (idx + 1));
	g_global.fd[1] = (int *)malloc(sizeof(int) * (idx + 1));
	g_global.fd_in = 0;
	g_global.fd_out = 0;
}

void	redirect(void)
{
	int		idx;
	int		in_idx;

	malloc_fd();
	edit_cmd_argv();
	idx = 0;
	while (1)
	{
		if (g_global.fd_out > 0)
			dup2(g_global.fd[1][idx], STDOUT_FILENO);
		in_idx = 0;
		while (in_idx < g_global.fd_in)
		{
			dup2(g_global.fd[0][in_idx], STDIN_FILENO);
			redir_fork();
			in_idx++;
		}
		if (g_global.fd_in == 0)
			redir_fork();
		idx++;
		if (g_global.fd_out == 0 || idx >= g_global.fd_out)
			break ;
	}
}
