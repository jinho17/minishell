/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:51:42 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/18 13:50:58 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_cmds(int num1, int num2, char **cmds)
{
	cmds[num1++][num2] = 0;
	free(cmds[num1]);
	cmds[num1] = 0;
}

void	new_str(char **cmds, int *num1, int *num2, int trim)
{
	cmds[*num1][*num2] = 0;
	if (*num2 != 0)
		*num1 += 1;
	*num2 = 0;
	if (trim == ' ' && g_global.redir == 1)
		g_global.redir = 0;
	else if (trim == ' ' && g_global.redir == 0)
		g_global.redir = 1;
}

char	**split_cmd(int num1, int num2, char *str, char trim)
{
	char	**cmds;
	int		idx;

	g_global.redir = 0;
	idx = 0;
	cmds = cmd_malloc();
	while (str[idx])
	{
		if ((str[idx] == '\'' || str[idx] == '\"') && g_global.quote == 0)
			g_global.quote = str[idx];
		else if (str[idx] == g_global.quote)
			g_global.quote = 0;
		else if ((str[idx] == '>' || str[idx] == '<') && trim == ' '
			&& g_global.quote == 0 && g_global.redir == 0)
			new_str(cmds, &num1, &num2, trim);
		else if (str[idx] != '>' && str[idx] != '<' && g_global.redir == 1)
			new_str(cmds, &num1, &num2, trim);
		if (str[idx] == trim && g_global.quote == 0)
			new_str(cmds, &num1, &num2, trim);
		else
			cmds[num1][num2++] = str[idx];
		idx++;
	}
	end_of_cmds(num1, num2, cmds);
	return (cmds);
}
