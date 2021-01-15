/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_cmd_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:40:22 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/13 16:51:54 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_redir(int idx, char **cmds)
{
	if (cmds[idx + 2] == 0)
	{
		while (cmds[idx])
			cmds[idx++] = 0;
	}
	else
	{
		while (cmds[idx + 2])
		{
			cmds[idx] = cmds[idx + 2];
			idx++;
		}
	}
	cmds[idx] = 0;
}

void	redir_input(int idx, char **cmds)
{
	if (cmds[idx + 1])
	{
		if ((g_global.fd[0][g_global.fd_in++] =
				open(cmds[idx + 1], O_RDONLY)) < 0)
		{
			ft_putstr_fd("./minishell: No such file or directory: ", 1);
			ft_putstr_fd(cmds[idx + 1], 1);
			ft_putchar_fd('\n', 1);
			exit(1);
		}
		remove_redir(idx, cmds);
	}
}

void	redir_output(int idx, char **cmds, int double_redir)
{
	if (cmds[idx + 1])
	{
		if (double_redir == 0)
		{
			if ((g_global.fd[1][g_global.fd_out++] = open(cmds[idx + 1],
					O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
				exit(1);
		}
		else
		{
			if ((g_global.fd[1][g_global.fd_out++] = open(cmds[idx + 1],
					O_CREAT | O_WRONLY | O_APPEND, 0644)) < 0)
				exit(1);
		}
		remove_redir(idx, cmds);
	}
}

int		is_inout(int *idx, char **cmds)
{
	while (cmds[*idx])
	{
		if (ft_strncmp(cmds[*idx], "<", 2) == 0)
			return (1);
		else if (ft_strncmp(cmds[*idx], ">", 2) == 0)
			return (2);
		else if (ft_strncmp(cmds[*idx], ">>", 3) == 0)
			return (3);
		else if (cmds[*idx][0] == '>' || cmds[*idx][0] == '<')
			return (4);
		*idx += 1;
	}
	return (-1);
}

void	edit_cmd_argv(void)
{
	int		idx;
	int		rtn;

	idx = 0;
	while (g_global.cmd_argv[idx])
	{
		rtn = is_inout(&idx, g_global.cmd_argv);
		if (rtn == 4
			|| (rtn != -1 && g_global.cmd_argv[idx + 1] == 0)
			|| (rtn != -1 && idx > 0 && (g_global.cmd_argv[idx - 1][0] == '>'
			|| g_global.cmd_argv[idx - 1][0] == '<')))
		{
			ft_putstr_fd("./minishell: parse error near '\\n'\n", 1);
			exit(1);
		}
		if (rtn == 1)
			redir_input(idx, g_global.cmd_argv);
		else if (rtn == 2)
			redir_output(idx, g_global.cmd_argv, 0);
		else if (rtn == 3)
			redir_output(idx, g_global.cmd_argv, 1);
	}
}
