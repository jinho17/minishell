/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 19:29:36 by jinkim            #+#    #+#             */
/*   Updated: 2020/12/30 04:00:01 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_env(int idx, int option)
{
	char	*name;
	char	*value;

	value = NULL;
	if (g_global.cmd_argv[idx][0] == '$')
	{
		name = ft_substr(g_global.cmd_argv[idx],
				1, ft_strlen(g_global.cmd_argv[idx]));
		value = find_env_value(g_lstenv, name);
		free(name);
		if ((idx - option > 1) && value != 0)
			ft_putchar_fd(' ', 1);
		if (value != 0)
			ft_putstr_fd(value, 1);
	}
	else
	{
		if (idx - option > 1)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(g_global.cmd_argv[idx], 1);
	}
}

void	cmd_echo(void)
{
	int		rtn;
	int		idx;

	if ((rtn = ft_strncmp(g_global.cmd_argv[1], "-n", 3)) == 0)
	{
		idx = 2;
		while (g_global.cmd_argv[idx] != 0)
			echo_env(idx++, 1);
	}
	else
	{
		idx = 1;
		while (g_global.cmd_argv[idx] != 0)
			echo_env(idx++, 0);
		ft_putchar_fd('\n', 1);
	}
}
