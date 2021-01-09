/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 02:16:27 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/09 00:48:36 by jinkim           ###   ########.fr       */
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
	ft_close(g_global.fd_in);
	if (cmds[idx + 1])
	{
		if ((g_global.fd_in = open(cmds[idx + 1], O_RDONLY)) < 0)
		{
			ft_putstr_fd("./minishell: No such file or directory: ", 1);
			ft_putstr_fd(cmds[idx + 1], 1);
			ft_putchar_fd('\n', 1);
			return ;
		}
	}
}

void	redir_output(int idx, char **cmds, int double_redir)
{
	ft_close(g_global.fd_out);
	if (cmds[idx + 1])
	{
		if (double_redir == 0)
		{
			if ((g_global.fd_out = open(cmds[idx + 1],
					O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
				return ;
		}
		else
		{
			if ((g_global.fd_out = open(cmds[idx + 1],
					O_CREAT | O_WRONLY | O_APPEND, 0644)) < 0)
				return ;
		}
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
		*idx += 1;
	}
	return (-1);
}

char	**redir_cmds_malloc(void)
{
	char	**cmds;
	int		idx;
	int		rtn;
	int		redir_num;

	redir_num = 0;
	rtn = is_inout(&redir_num, g_global.cmd_argv);
	if (rtn != -1)
	{
		cmds = cmd_malloc();
		idx = 0;
		while (g_global.cmd_argv[idx])
		{
			cmds[idx] = ft_strdup(g_global.cmd_argv[idx]);
			idx++;
		}
		cmds[idx] = 0;
		free_str_2p(g_global.cmd_argv);
		g_global.cmd_argv = cmd_malloc();
		idx = 0;
		while (idx < redir_num)
		{
			g_global.cmd_argv[idx] = ft_strdup(cmds[idx]);
			idx++;
		}
		g_global.cmd_argv[idx] = 0;
	}
	else
		return (0);
	return(cmds);
}
