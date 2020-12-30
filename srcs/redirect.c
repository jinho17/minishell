/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 02:16:27 by jinkim            #+#    #+#             */
/*   Updated: 2020/12/30 04:22:53 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_input(int idx)
{
	int		fd;

	if (g_global.cmd_argv[idx + 1])
	{
		if ((fd = open(g_global.cmd_argv[idx + 1], O_RDONLY)) < 0)
		{
			ft_putstr_fd("./minishell: No such file or directory: ", 1);
			ft_putstr_fd(g_global.cmd_argv[idx + 1], 1);
			ft_putchar_fd('\n', 1);
			return ;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		while (g_global.cmd_argv[idx + 2])
		{
			g_global.cmd_argv[idx] = g_global.cmd_argv[idx + 2];
			idx++;
		}
		g_global.cmd_argv[idx] = 0;
	}
}

void	redir_output(int idx)
{
	int		fd;

	if (g_global.cmd_argv[idx + 1])
	{
		if ((fd = open(g_global.cmd_argv[idx + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
			return ;
		g_global.redir_out = 1;
		dup2(fd, STDOUT_FILENO);
		close(fd);
		while (g_global.cmd_argv[idx + 2])
		{
			g_global.cmd_argv[idx] = g_global.cmd_argv[idx + 2];
			idx++;
		}
		g_global.cmd_argv[idx] = 0;
	}
}

void	redirect(void)
{
	int		idx;
	int		rtn;

	idx = 0;
	g_global.redir_out = 0;
	while (g_global.cmd_argv[idx])
	{
		if ((rtn = ft_strncmp(g_global.cmd_argv[idx], "<", 2)) == 0)
		{
			redir_input(idx);
			break ;
		}
		else if ((rtn = ft_strncmp(g_global.cmd_argv[idx], ">", 2)) == 0)
		{
			redir_output(idx);
			break ;
		}
		idx++;
	}
}
