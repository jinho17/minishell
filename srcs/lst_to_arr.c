/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 21:33:59 by jinkim            #+#    #+#             */
/*   Updated: 2020/12/28 18:17:54 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_lst_cmd(char **env_arr)
{
	char	*cmd;
	char	*tmp;
	int		idx;
	t_lst	*curr;

	curr = g_lstenv;
	idx = 0;
	while (curr != NULL)
	{
		tmp = ft_strjoin(curr->name, "=");
		cmd = ft_strjoin(tmp, curr->value);
		env_arr[idx] = ft_strdup(cmd);
		idx++;
		free(tmp);
		free(cmd);
		curr = curr->next;
	}
	env_arr[idx] = 0;
}

char	**lst_to_arr(void)
{
	char	**env_arr;
	int		lstnum;
	t_lst	*curr;

	lstnum = 0;
	curr = g_lstenv;
	while (curr != NULL)
	{
		lstnum++;
		curr = curr->next;
	}
	env_arr = (char **)malloc(sizeof(char *) * (lstnum + 1));
	copy_lst_cmd(env_arr);
	return (env_arr);
}
