/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 06:54:02 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/18 13:42:25 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_2p(char **str)
{
	int		idx;

	idx = 0;
	while ((str[idx] != NULL && g_global.malloc_num == 0) ||
		(idx < g_global.malloc_num && g_global.malloc_num != 0))
	{
		free(str[idx]);
		idx++;
	}
	free(str);
}

void	parent_ps(void)
{
	int	status;

	status = 0;
	wait(&status);
	if (WEXITSTATUS(status) != 0)
	{
		g_global.bef_quit = 1;
		return ;
	}
	else
		g_global.bef_quit = 0;
	if (ft_strncmp(g_global.cmd_argv[0], "exit", 5) == 0)
		cmd_exit();
	else if (ft_strncmp(g_global.cmd_argv[0], "cd", 3) == 0)
		cmd_cd();
	else if (ft_strncmp(g_global.cmd_argv[0], "export", 7) == 0
			&& g_global.cmd_argv[1] != 0)
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
}

void	exec_cmd(void)
{
	pid_t	pid;
	int		idx;

	if (ft_strncmp(g_global.cmd, "", 2) == 0 || g_global.cmd_argv[0] == 0)
	{
		g_global.bef_quit = 1;
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		idx = 0;
		if (is_inout(&idx, g_global.cmd_argv) > 0)
			redirect();
		else
			child_ps();
		exit(0);
	}
	else if (pid > 0)
		parent_ps();
	else
		exit(1);
}
