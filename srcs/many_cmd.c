/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   many_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:30:03 by jinkim            #+#    #+#             */
/*   Updated: 2020/12/30 04:28:02 by jinkim           ###   ########.fr       */
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

void	child_ps(void)
{
	char	*bin_file;
	int		rtn;
	char	**env_arr;

	bin_file = ft_strjoin("/bin/", g_global.cmd_argv[0]);
	env_arr = lst_to_arr();
	rtn = execve(bin_file, g_global.cmd_argv, env_arr);
	if (rtn == -1)
	{
		ft_putstr_fd("./minishell: ", 1);
		ft_putstr_fd(g_global.cmd_argv[0], 1);
		ft_putstr_fd(": command not found\n", 1);
	}
	free_str_2p(env_arr);
	exit(0);
}

void	exec_cmd(void)
{
	if (ft_strncmp(g_global.cmd, "", 2) == 0)
		return ;
	else if (ft_strncmp(g_global.cmd_argv[0], "exit", 5) == 0)
		cmd_exit();
	redirect();
	if (ft_strncmp(g_global.cmd_argv[0], "env", 4) == 0 && g_global.cmd_argv[1] == 0)
		cmd_env_export(g_lstenv);
	else if (ft_strncmp(g_global.cmd_argv[0], "env", 4) == 0 && g_global.cmd_argv[1] != 0)
		return ;
	else if (ft_strncmp(g_global.cmd_argv[0], "cd", 3) == 0 && g_global.cmd_argv[2] == 0)
		cmd_cd();
	else if (ft_strncmp(g_global.cmd_argv[0], "export", 7) == 0 && g_global.cmd_argv[1] == 0)
		cmd_env_export(g_lstexport);
	else if (ft_strncmp(g_global.cmd_argv[0], "export", 7) == 0 && g_global.cmd_argv[1] != 0)
		cmd_export();
	else if (ft_strncmp(g_global.cmd_argv[0], "echo", 5) == 0 && g_global.cmd_argv[1] != 0)
		cmd_echo();
	else if (ft_strncmp(g_global.cmd_argv[0], "unset", 6) == 0)
		cmd_unset();
	else
	{
		g_global.pid = fork();
		if (g_global.pid == 0)
			child_ps();
		else if (g_global.pid > 0)
			wait(0);
		else
			cmd_exit();
	}
	if (g_global.redir_out == 1)
	{
		g_global.redir_out = 0;
		close(STDOUT_FILENO);
	}
}

void	many_cmd(void)
{
	int		repeat;
	int		idx;
	char	**cmds;

	repeat = 0;
	idx = 0;
	while (g_global.cmd[idx] != 0)
	{
		if (g_global.cmd[idx] == ';')
			repeat++;
		idx++;
	}
	if (g_global.cmd[idx - 1] != ';')
		repeat++;
	cmds = ft_split(g_global.cmd, ';');
	idx = 0;
	while (idx < repeat && cmds[idx])
	{
		g_global.cmd_argv = ft_split(cmds[idx], ' ');
		if (g_global.cmd_argv[0])
			exec_cmd();
		free_str_2p(g_global.cmd_argv);
		idx++;
	}
	free_str_2p(cmds);
}
