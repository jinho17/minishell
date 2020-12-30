/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_many_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 04:07:55 by jinkim            #+#    #+#             */
/*   Updated: 2020/12/29 04:08:26 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_exec_cmd(int *num1, int *num2, int semi_colon)
{
	g_global.cmd_argv[*num1][*num2] = '\0';
	*num1 += 1;
	g_global.cmd_argv[*num1] = 0;
	exec_cmd();
	if (semi_colon == 1)
	{
		free_str_2p(g_global.cmd_argv);
		cmd_argv_malloc();
		*num1 = 0;
		*num2 = 0;
	}
}

void	quote_space(int *num1, int *num2)
{
	g_global.cmd_argv[*num1][*num2] = '\0';
	if (*num2 != 0)
		*num1 += 1;
	*num2 = 0;
}

void	cmd_argv_malloc(void)
{
	int		idx;
	int		space;

	idx = 0;
	space = 0;
	while (g_global.cmd[idx])
	{
		if (g_global.cmd[idx] == ' ')
			space++;
		idx++;
	}
	g_global.cmd_argv = (char **)malloc(sizeof(char *) * (space + 2));
	idx = 0;
	while (idx < space + 2)
	{
		g_global.cmd_argv[idx] = (char *)malloc(
			sizeof(char) * (int)ft_strlen(g_global.cmd));
		idx++;
	}
}

void	quote_many_cmd(int quote)
{
	int		idx;
	int		num1;
	int		num2;

	cmd_argv_malloc();
	idx = 0;
	num1 = 0;
	num2 = 0;
	while (g_global.cmd[idx])
	{
		if ((g_global.cmd[idx] == '\'' || g_global.cmd[idx] == '\"')
			&& quote == 1)
			quote = g_global.cmd[idx];
		else if (quote != 1 && g_global.cmd[idx] == quote)
			quote = 1;
		else if (g_global.cmd[idx] == ' ' && quote == 1)
			quote_space(&num1, &num2);
		else if (g_global.cmd[idx] == ';' && quote == 1)
			quote_exec_cmd(&num1, &num2, 1);
		else
			g_global.cmd_argv[num1][num2++] = g_global.cmd[idx];
		idx++;
	}
	if (g_global.cmd[idx - 1] != ';')
		quote_exec_cmd(&num1, &num2, 0);
}
