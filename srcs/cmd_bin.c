/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 08:29:07 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/07 23:13:03 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_echo_bin(void)
{
	int		idx;

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

void	cmd_bin(void)
{
	int		rtn;
	char	*bin_file;
	char	**env_arr;

	if (ft_strncmp(g_global.cmd_argv[0], "echo", 5) == 0 && g_global.cmd_argv[1])
		cmd_echo_bin();
	bin_file = ft_strjoin("/bin/", g_global.cmd_argv[0]);
	env_arr = lst_to_arr();
	rtn = execve(bin_file, g_global.cmd_argv, env_arr);
	if (rtn == -1)
	{
		free(bin_file);
		bin_file = ft_strjoin("/usr/bin/", g_global.cmd_argv[0]);
		rtn = execve(bin_file, g_global.cmd_argv, env_arr);
		if (rtn == -1)
		{
			ft_putstr_fd("./minishell: ", 1);
			ft_putstr_fd(g_global.cmd_argv[0], 1);
			ft_putstr_fd(": command not found\n", 1);
		}
	}
	free(bin_file);
	free_str_2p(env_arr);
}
