/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 09:22:05 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/08 21:37:38 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_print(void)
{
	char	cwd[1024];
	int		rtn;

	if (g_global.cmd_argv[1] != 0)
	{
		ft_putstr_fd("pwd: too many arguments\n", 1);
		return ;
	}
	getcwd(cwd, sizeof(cwd));
	rtn = chdir(cwd);
	if ((ft_strncmp(cwd, g_global.cwd, ft_strlen(cwd)) != 0)
		&& rtn != 0)
		ft_putstr_fd(".", 1);
	else
		ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
}

void	cmd_exit(void)
{
	exit(0);
}

void	cmd_cd(void)
{
	int		rtn;
	char	*tmp;

	if (g_global.cmd_argv[1] == 0)
	{
		free_str_2p(g_global.cmd_argv);
		tmp = ft_strjoin("cd /Users/", find_env_value(g_lstenv, "USER"));
		g_global.cmd_argv = ft_split(tmp, ' ');
		free(tmp);
	}
	if (g_global.cmd_argv[2] == 0)
	{
		rtn = chdir(g_global.cmd_argv[1]);
		if (rtn != 0)
		{
			ft_putstr_fd("./minishell: cd: No such file or directory: ", 1);
			ft_putstr_fd(g_global.cmd_argv[1], 1);
			ft_putchar_fd('\n', 1);
		}
	}
}

void	cmd_env_export(t_lst *lst)
{
	while (lst != NULL)
	{
		ft_putstr_fd(lst->name, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(lst->value, 1);
		ft_putchar_fd('\n', 1);
		lst = lst->next;
	}
}
