/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:11:03 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/13 16:54:10 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		str_equal(char *str)
{
	int		idx;
	int		cnt;

	if (str[0] == '=')
	{
		g_global.export_err = -1;
		return (-1);
	}
	idx = 0;
	cnt = 0;
	while (str[idx] != 0)
	{
		if (str[idx] == '=')
			cnt++;
		idx++;
	}
	return (cnt);
}

void	export_not_valid(char *str)
{
	ft_putstr_fd("export: not valid in this context: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	g_global.bef_quit = 1;
}

int		export_isalnum(char *str)
{
	int		idx;

	idx = 0;
	if (ft_isdigit(str[0]) == 1)
	{
		g_global.export_err = -1;
		return (-1);
	}
	while (str[idx] != 0)
	{
		if ((ft_isalnum(str[idx]) == 0) && str[idx] == '=')
			return (1);
		if ((ft_isalnum(str[idx]) == 0) && (str[idx] != '='))
		{
			g_global.export_err = -1;
			return (-1);
		}
		idx++;
	}
	return (1);
}

void	cmd_export(void)
{
	int		idx;
	int		rtn;

	idx = 1;
	while (g_global.cmd_argv[idx] != 0)
	{
		if ((rtn = export_isalnum(g_global.cmd_argv[idx])) < 0)
		{
			export_not_valid(g_global.cmd_argv[idx]);
			return ;
		}
		else
		{
			if ((rtn = str_equal(g_global.cmd_argv[idx])) < 0)
			{
				export_not_valid(g_global.cmd_argv[idx]);
				return ;
			}
			else
				edit_lst(g_global.cmd_argv[idx]);
		}
		idx++;
	}
	g_global.bef_quit = 0;
}
