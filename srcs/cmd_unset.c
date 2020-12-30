/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 22:22:25 by jinkim            #+#    #+#             */
/*   Updated: 2020/12/27 23:30:35 by jinkim           ###   ########.fr       */
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
}

void	cmd_unset(void)
{
	int		rtn;
	char	*value;
	int		idx;

	if (g_global.cmd_argv[1] == 0)
		ft_putstr_fd("unset: not enough arguments\n", 1);
	else
	{
		idx = 1;
		while (g_global.cmd_argv[idx] != 0)
		{
			if ((rtn = str_isalnum(g_global.cmd_argv[idx])) < 0)
			{
				unset_invalid();
				break ;
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

	}
}
