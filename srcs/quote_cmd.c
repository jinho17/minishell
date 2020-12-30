/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 20:10:07 by jinkim            #+#    #+#             */
/*   Updated: 2020/12/29 04:08:28 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_quote(int quote)
{
	if (quote == '\'')
		ft_putstr_fd("quote> ", 1);
	else if (quote == '\"')
		ft_putstr_fd("dquote> ", 1);
}

char	need_more_cmd(char quote, char *tmp, char *buf)
{
	tmp = ft_strjoin(g_global.cmd, "\n");
	buf[0] = 0;
	buf[1] = '\0';
	free(g_global.cmd);
	print_quote(quote);
	while (1)
	{
		read(1, buf, 1);
		if (quote == 1 && buf[0] == '\n')
			break ;
		else if (buf[0] == quote)
			quote = 1;
		else if ((buf[0] == '\'' || buf[0] == '\"') && quote == 1)
			quote = buf[0];
		else if (buf[0] == '\n')
			print_quote(quote);
		g_global.cmd = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = ft_strdup(g_global.cmd);
		free(g_global.cmd);
	}
	g_global.cmd = ft_strdup(tmp);
	free(tmp);
	return (quote);
}

void	quote_cmd(char quote)
{
	char	*tmp;
	char	buf[2];

	tmp = NULL;
	if (quote != 1)
		quote = need_more_cmd(quote, tmp, buf);
	quote_many_cmd(quote);
}
