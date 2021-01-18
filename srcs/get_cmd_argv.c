/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:39:20 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/18 13:42:20 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pipe_check(char *str)
{
	int		idx;

	idx = 0;
	while (str[idx])
	{
		if ((str[idx] == '\'' || str[idx] == '\"') && g_global.quote == 0)
			g_global.quote = str[idx];
		else if (str[idx] == g_global.quote)
			g_global.quote = 0;
		else if (str[idx] == '|' && g_global.quote == 0)
			return (1);
		idx++;
	}
	return (0);
}

char	**cmd_malloc(void)
{
	int		idx;
	int		space;
	char	**rtn;

	idx = 0;
	space = 0;
	while (g_global.cmd[idx])
	{
		if (g_global.cmd[idx] == ' ' || g_global.cmd[idx] == ';' ||
			g_global.cmd[idx] == '|' || g_global.cmd[idx] == '<' ||
			g_global.cmd[idx] == '>')
			space++;
		idx++;
	}
	g_global.malloc_num = space * space + 5;
	rtn = (char **)malloc(sizeof(char *) * g_global.malloc_num);
	idx = 0;
	while (idx < g_global.malloc_num)
	{
		rtn[idx] = (char *)malloc(
			sizeof(char) * ((int)ft_strlen(g_global.cmd) + 1));
		idx++;
	}
	return (rtn);
}

void	remove_space(char **cmds)
{
	char	*tmp;
	int		idx;

	idx = 0;
	while (cmds[idx])
	{
		tmp = ft_strtrim(cmds[idx], " ");
		free(cmds[idx]);
		cmds[idx] = ft_strdup(tmp);
		free(tmp);
		idx++;
	}
}

void	get_cmd_argv(void)
{
	int		idx;
	char	**cmds;

	idx = 0;
	cmds = split_cmd(0, 0, g_global.cmd, ';');
	remove_empty_str(cmds, 0);
	remove_space(cmds);
	idx = 0;
	while (cmds[idx])
	{
		g_global.export_err = 1;
		if (pipe_check(cmds[idx]) == 1)
			pipe_version(cmds, idx);
		else
		{
			no_pipe_version(cmds, idx);
			if (g_global.export_err == -1)
			{
				free_str_2p(cmds);
				return ;
			}
		}
		idx++;
	}
	free_str_2p(cmds);
}
