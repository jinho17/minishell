/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:00:35 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/11 15:59:43 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*front_strtrim(char *str)
{
	int		idx;
	char	*rtn;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] != ' ' && str[idx] != '\t')
			break ;
		idx++;
	}
	rtn = ft_substr(str, idx, ft_strlen(str));
	return (rtn);
}

void	print_quote(void)
{
	int idx;

	idx = 0;
	while (idx < g_global.pipe_num)
	{
		ft_putstr_fd("pipe ", 1);
		idx++;
	}
	if (g_global.quote == '\'')
		ft_putstr_fd("quote> ", 1);
	else if (g_global.quote == '\"')
		ft_putstr_fd("dquote> ", 1);
	else if (g_global.quote == 0 && g_global.pipe == 1)
		ft_putstr_fd("> ", 1);
}

void	check_condition(char *buf, int space_check)
{
	if (buf[0] == '|' && g_global.quote == 0 && g_global.pipe == 1)
		g_global.pipe = -1;
	else if (buf[0] == '|' && g_global.pipe_num == 0 && space_check == 0)
		g_global.pipe = -1;
	else if (buf[0] == '|' && g_global.semi_c == 1 && g_global.pipe == 0)
		g_global.pipe = -1;
	else if (buf[0] == '|' && g_global.quote == 0 && g_global.pipe == 0)
	{
		g_global.pipe = 1;
		g_global.pipe_num++;
	}
	else if (buf[0] != ' ' && buf[0] != '\n'
		&& buf[0] != ';' && g_global.pipe == 1)
	{
		g_global.pipe_num = 0;
		g_global.pipe = 0;
	}
	else if (buf[0] != ';' && buf[0] != '|'
	&& buf[0] != ' ' && g_global.semi_c == 1)
		g_global.semi_c = 0;
}

void	quote_pipe_cond(char *buf, int *space_check)
{
	if (buf[0] != ' ' && buf[0] != '\t' && buf[0] != '|'
		&& *space_check == 0)
		*space_check = 1;
	if (buf[0] == g_global.quote)
		g_global.quote = 0;
	else if ((buf[0] == '\'' || buf[0] == '\"') && g_global.quote == 0)
		g_global.quote = buf[0];
	else if (buf[0] == ';' && g_global.quote == 0 && g_global.semi_c == 0)
		g_global.semi_c = 1;
	else if (buf[0] == ';' && g_global.semi_c == 1)
		g_global.semi_c = -1;
	check_condition(buf, *space_check);
}

void	read_cmd(char *buf, int space_check)
{
	char	*tmp;

	tmp = ft_strdup(buf);
	while (1)
	{
		read(0, buf, 1);
		if (buf[0] == '\n' && g_global.pipe == 0 && g_global.quote == 0)
			break ;
		else if (buf[0] == '\n' &&
			(g_global.pipe == -1 || g_global.semi_c == -1))
			break ;
		quote_pipe_cond(buf, &space_check);
		if (buf[0] == '\n')
		{
			print_quote();
			if (g_global.pipe == 1)
				continue ;
		}
		g_global.cmd = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = ft_strdup(g_global.cmd);
		free(g_global.cmd);
	}
	g_global.cmd = front_strtrim(tmp);
	free(tmp);
}
