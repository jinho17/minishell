/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 09:28:57 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/08 04:59:33 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_cmd(void)
{
	char	buf[2];

	read(1, buf, 1);
	buf[1] = '\0';
	if (buf[0] == '\'' || buf[0] == '\"')
		g_global.quote = buf[0];
	else if (buf[0] == '\n')
		return (-1);
	read_cmd(buf, 0);
	if (g_global.cmd[0] == '|')
		ft_putstr_fd("./minishell: parse error near '|'\n", 1);
	if (g_global.cmd[0] == '\n' || g_global.cmd[0] == '|'
		|| g_global.cmd[0] == 0 || g_global.pipe == -1)
		return (-1);
	else if (g_global.semi_c == -1)
	{
		ft_putstr_fd("./minishell: parse error near `;;'\n", 1);
		return (-1);
	}
	return (1);
}

void	shell_prompt(void)
{
	getcwd(g_global.cwd, sizeof(g_global.cwd));
	ft_putstr_fd(find_env_value(g_lstenv, "USER"), 1);
	ft_putchar_fd('@', 1);
	ft_putstr_fd("minishell:", 1);
	ft_putstr_fd(g_global.cwd, 1);
	ft_putstr_fd("$ ", 1);
}

int		main(int argc, char *argv[], char **envp)
{
	argc = 0;
	argv = NULL;

	init_lst(envp);
	while (1)
	{
		g_global.quote = 0;
		g_global.pipe_num = 0;
		g_global.pipe = 0;
		g_global.semi_c = 0;
		shell_prompt();
		if (get_cmd() < 0)
			continue ;
		get_cmd_argv();
	}

	//while(g_lstenv != NULL)
	//{
	//		t_lst *next = g_lstenv->next;
	//		free(g_lstenv->name);
	//		free(g_lstenv->value);
	//		free(g_lstenv);
	//		g_lstenv = next;
	//}
	//free(g_lstenv);

	//free(g_lstexport);
	//while(1) ;

	return 0;
}
