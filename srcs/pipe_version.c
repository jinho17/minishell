/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_version.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 05:48:52 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/15 10:07:59 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_empty_str(char **cmds, int idx)
{
	int		num;

	while (cmds[idx])
	{
		if (cmds[idx][0] == 0)
		{
			num = idx;
			while (cmds[num])
			{
				if (cmds[num + 1])
				{
					free(cmds[num]);
					cmds[num] = ft_strdup(cmds[num + 1]);
				}
				else
					cmds[num] = 0;
				num++;
			}
			cmds[num] = 0;
		}
		else
			idx++;
	}
}

void	move_1char(int num1, int num2)
{
	while (g_global.cmd_argv[num1][num2])
	{
		g_global.cmd_argv[num1][num2] = g_global.cmd_argv[num1][num2 + 1];
		num2++;
	}
	g_global.cmd_argv[num1][num2] = 0;
}

void	remove_quote(void)
{
	int		num1;
	int		num2;

	num1 = 0;
	while (g_global.cmd_argv[num1])
	{
		num2 = 0;
		while (g_global.cmd_argv[num1][num2])
		{
			if ((g_global.cmd_argv[num1][num2] == '\'' ||
				g_global.cmd_argv[num1][num2] == '\"') && g_global.quote == 0)
			{
				g_global.quote = g_global.cmd_argv[num1][num2];
				move_1char(num1, num2);
			}
			else if (g_global.cmd_argv[num1][num2] == g_global.quote)
			{
				g_global.quote = 0;
				move_1char(num1, num2);
			}
			else
				num2++;
		}
		num1++;
	}
}

void	no_pipe_version(char **cmds, int idx)
{
	g_global.cmd_argv = split_cmd(0, 0, cmds[idx], ' ');
	dollar_change();
	remove_quote();
	remove_empty_str(g_global.cmd_argv, 0);
	path_change(0, 0, find_env_value(g_lstenv, "PATH"));
	exec_cmd();
	free_str_2p(g_global.cmd_argv);
}

void	pipe_version(char **cmds, int idx)
{
	char	**pipe_cmd;

	pipe_cmd = split_cmd(0, 0, cmds[idx], '|');
	remove_space(pipe_cmd);
	exec_pipe(pipe_cmd);
	free_str_2p(pipe_cmd);
}
