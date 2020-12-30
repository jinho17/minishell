/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 09:22:05 by jinkim            #+#    #+#             */
/*   Updated: 2020/12/27 21:05:23 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_exit(void)
{
	exit(1);
}

void	cmd_cd(void)
{
	int rtn;

	rtn = chdir(g_global.cmd_argv[1]);
	if (rtn != 0)
	{
		ft_putstr_fd("./minishell: cd: No such file or directory: ", 1);
		ft_putstr_fd(g_global.cmd_argv[1], 1);
		ft_putchar_fd('\n', 1);
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
