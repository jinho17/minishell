/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 06:54:02 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/09 00:48:39 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_2p(char **str)
{
	int		idx;

	idx = 0;
	while (str[idx] != NULL)
	{
		free(str[idx]);
		idx++;
	}
	free(str);
}

void	parent_ps(void)
{

	if (ft_strncmp(g_global.cmd_argv[0], "exit", 5) == 0)
		cmd_exit();
	else if (ft_strncmp(g_global.cmd_argv[0], "cd", 3) == 0)
		cmd_cd();
	else if (ft_strncmp(g_global.cmd_argv[0], "export", 7) == 0 && g_global.cmd_argv[1] != 0)
		cmd_export();
	else if (ft_strncmp(g_global.cmd_argv[0], "unset", 6) == 0)
		cmd_unset();
}

void	child_ps(void)
{
	if (ft_strncmp(g_global.cmd_argv[0], "env", 4) == 0
		&& g_global.cmd_argv[1] == 0)
		cmd_env_export(g_lstenv);
	else if (ft_strncmp(g_global.cmd_argv[0], "env", 4) == 0
		&& g_global.cmd_argv[1] != 0)
		exit(1);
	else if (ft_strncmp(g_global.cmd_argv[0], "export", 7) == 0
		&& g_global.cmd_argv[1] == 0)
		cmd_env_export(g_lstexport);
	else if (ft_strncmp(g_global.cmd_argv[0], "pwd", 4) == 0)
		pwd_print();
	else if (ft_strncmp(g_global.cmd_argv[0], "cd", 3) != 0
		&& ft_strncmp(g_global.cmd_argv[0], "export", 7) != 0
		&& ft_strncmp(g_global.cmd_argv[0], "unset", 6) != 0
		&& ft_strncmp(g_global.cmd_argv[0], "exit", 5) != 0)
		cmd_bin();
	exit(0);
}

void	exec_cmd(void)
{
	char	**cmds;
	int		idx;
	int		rtn;

	cmds = redir_cmds_malloc();
	if (ft_strncmp(g_global.cmd, "", 2) == 0 || g_global.cmd_argv[0] == 0)
		return ;
	if (cmds != 0)
	{
		idx = 0;
		while((rtn = is_inout(&idx, cmds)) > 0)
		{
			if (rtn == 1)
				redir_input(idx, cmds);
			else if (rtn == 2)
				redir_output(idx, cmds, 0);
			else if (rtn == 3)
				redir_output(idx, cmds, 1);
			g_global.pid = fork();
			if (g_global.pid == 0)
			{
				if (rtn == 1)
					dup2(g_global.fd_in, STDIN_FILENO);
				else if (rtn == 2 || rtn == 3)
					dup2(g_global.fd_out, STDOUT_FILENO);
				child_ps();
			}
			else if (g_global.pid > 0)
			{
				parent_ps();
				while (wait(0) > 0)
					;
				if (rtn != -1 && cmds[idx + 1])
					remove_redir(idx, cmds);
				else if (rtn != -1)
					cmds[idx] = 0;
			}
			else
				exit(1);
		}
		free_str_2p(cmds);
	}
	else
	{
		g_global.pid = fork();
		if (g_global.pid == 0)
			child_ps();
		else if (g_global.pid > 0)
		{
			wait(0);
			parent_ps();
		}
		else
			exit(1);
	}
}
