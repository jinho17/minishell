/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_change.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 02:54:45 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/08 21:27:28 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_value(int idx, int num, int *len, char *value)
{
	char	*s1;
	char	*s2;
	char	*tmp;

	if (num > 0)
	{
		s2 = ft_substr(g_global.cmd_argv[idx], 0, num);
		s1 = ft_strjoin(s2, value);
		free(s2);
	}
	else
		s1 = ft_strdup(value);
	if (*len < (int)ft_strlen(g_global.cmd_argv[idx]))
	{
		s2 = ft_substr(g_global.cmd_argv[idx],
			*len, ft_strlen(g_global.cmd_argv[idx]));
		tmp = ft_strjoin(s1, s2);
		free(s2);
	}
	else
		tmp = ft_strdup(s1);
	*len = ft_strlen(s1);
	free(s1);
	free(g_global.cmd_argv[idx]);
	return (tmp);
}

int		get_len(int idx, int len)
{
	if (ft_isdigit(g_global.cmd_argv[idx][len]) == 1)
	{
		while (ft_isdigit(g_global.cmd_argv[idx][len]))
			len++;
	}
	else
	{
		while (g_global.cmd_argv[idx][len])
		{
			if (g_global.cmd_argv[idx][len] == '$'
				|| g_global.cmd_argv[idx][len] == ' '
				|| g_global.cmd_argv[idx][len] == '='
				|| g_global.cmd_argv[idx][len] == '\''
				|| g_global.cmd_argv[idx][len] == '\"'
				|| g_global.cmd_argv[idx][len] == '/')
				break ;
			len++;
		}
	}
	return (len);
}

int		dollar_value(int idx, int num)
{
	char	*name;
	char	*value;
	int		len;

	len = get_len(idx, num + 1);
	if (len - num == 1)
		return (len);
	name = ft_substr(g_global.cmd_argv[idx], num + 1, len - num - 1);
	if (find_env_value(g_lstenv, name) != NULL)
		value = ft_strdup(find_env_value(g_lstenv, name));
	else
		value = ft_strdup("");
	free(name);
	g_global.cmd_argv[idx] = change_value(idx, num, &len, value);
	free(value);
	return (len);
}

void	dollar_change(void)
{
	int		idx;
	int		num;

	idx = 0;
	while (g_global.cmd_argv[idx])
	{
		num = 0;
		while (g_global.cmd_argv[idx][num])
		{
			if (g_global.cmd_argv[idx][num] == '\'' && g_global.quote == 0)
				g_global.quote = g_global.cmd_argv[idx][num];
			else if (g_global.cmd_argv[idx][num] == g_global.quote)
				g_global.quote = 0;
			if (g_global.cmd_argv[idx][num] == '$' && g_global.quote == 0)
				num = dollar_value(idx, num);
			else
				num++;
		}
		idx++;
	}
}
