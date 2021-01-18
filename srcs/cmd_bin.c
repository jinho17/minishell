/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 08:29:07 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/18 02:14:21 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_echo_bin(void)
{
	int		idx;
	char	*tmp;

	tmp = ft_strjoin("/bin/", g_global.cmd_argv[0]);
	free(g_global.cmd_argv[0]);
	g_global.cmd_argv[0] = ft_strdup(tmp);
	free(tmp);
	if (g_global.cmd_argv[1])
	{
		if (ft_strncmp(g_global.cmd_argv[1], "-n", 3) == 0)
		{
			while (ft_strncmp(g_global.cmd_argv[2], "-n", 3) == 0)
			{
				idx = 2;
				while (g_global.cmd_argv[idx])
				{
					g_global.cmd_argv[idx] = g_global.cmd_argv[idx + 1];
					idx++;
				}
				g_global.cmd_argv[idx] = 0;
			}
		}
	}
}

void	cmd_bin(void)
{
	int		rtn;
	char	**env_arr;

	if (ft_strncmp(g_global.cmd_argv[0], "echo", 5) == 0)
		cmd_echo_bin();
	env_arr = lst_to_arr();
	rtn = execve(g_global.cmd_argv[0], g_global.cmd_argv, env_arr);
	if (rtn == -1)
	{
		ft_putstr_fd("./minishell: ", 1);
		ft_putstr_fd(g_global.cmd_argv[0], 1);
		ft_putstr_fd(": command not found\n", 1);
		g_global.malloc_num = 0;
		free_str_2p(env_arr);
		exit(1);
	}
}
