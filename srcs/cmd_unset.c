/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 22:22:25 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/12 15:26:47 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_delete(t_lst *lst, char *name)
{
	t_lst	*curr;
	t_lst	*bef;

	curr = lst;
	bef = 0;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->name, name, ft_strlen(name) + 1) == 0)
			break ;
		bef = curr;
		curr = curr->next;
	}
	if (ft_strncmp(curr->name, name, ft_strlen(name) + 1) == 0)
	{
		bef->next = curr->next;
		free(curr->value);
		free(curr->name);
		free(curr);
	}
}

void	unset_invalid(void)
{
	ft_putstr_fd("unset: ", 1);
	ft_putstr_fd(g_global.cmd_argv[1], 1);
	ft_putstr_fd(": invalid parameter name\n", 1);
	g_global.bef_quit = 1;
}

int		unset_isalnum(char *str)
{
	int		idx;

	idx = 0;
	while (str[idx] != 0)
	{
		if (ft_isalnum(str[idx]) == 0)
			return (-1);
		idx++;
	}
	return (1);
}

void	run_unset(void)
{
	int		idx;
	int		rtn;
	char	*value;

	idx = 1;
	while (g_global.cmd_argv[idx] != 0)
	{
		if ((rtn = unset_isalnum(g_global.cmd_argv[idx])) < 0)
		{
			unset_invalid();
			return ;
		}
		else
		{
			value = find_env_value(g_lstenv, g_global.cmd_argv[idx]);
			if (value != 0)
			{
				lst_delete(g_lstenv, g_global.cmd_argv[idx]);
				lst_delete(g_lstexport, g_global.cmd_argv[idx]);
			}
		}
		idx++;
	}
	g_global.bef_quit = 0;
}

void	cmd_unset(void)
{
	if (g_global.cmd_argv[1] == 0)
	{
		ft_putstr_fd("unset: not enough arguments\n", 1);
		g_global.bef_quit = 1;
	}
	else
		run_unset();
}
