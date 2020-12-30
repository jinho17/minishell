/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:11:03 by jinkim            #+#    #+#             */
/*   Updated: 2020/12/27 00:22:26 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		str_equal(char *str)
{
	int		idx;
	int		cnt;

	if (str[0] == '=')
		return (-1);
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
}

int		str_isalnum(char *str)
{
	int		idx;

	idx = 0;
	while (str[idx] != 0)
	{
		if ((ft_isalnum(str[idx]) == 0) && (str[idx] != '='))
			return (-1);
		idx++;
	}
	return (1);
}

void	cmd_export(void)
{
	int		rtn;
	int		idx;

	idx = 1;
	while (g_global.cmd_argv[idx] != 0)
	{
		if ((rtn = str_isalnum(g_global.cmd_argv[idx])) < 0)
		{
			export_not_valid(g_global.cmd_argv[idx]);
			break ;
		}
		else
		{
			if ((rtn = str_equal(g_global.cmd_argv[idx])) < 0)
			{
				export_not_valid(g_global.cmd_argv[idx]);
				break ;
			}
			else
				edit_lst(g_global.cmd_argv[idx]);
		}
		idx++;
	}
}
