/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 09:28:57 by jinkim            #+#    #+#             */
/*   Updated: 2020/12/30 03:33:29 by jinkim           ###   ########.fr       */
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

char	get_cmd(void)
{
	char	buf[2];
	char	*tmp;
	char	quote;

	quote = 0;
	read(1, buf, 1);
	buf[1] = '\0';
	tmp = ft_strdup(buf);
	if (buf[0] == '\'' || buf[0] == '\"')
		quote = buf[0];
	while (buf[0] != '\n')
	{
		read(1, buf, 1);
		if (buf[0] == '\n')
			break ;
		else if ((buf[0] == '\'' || buf[0] == '\"') && (quote == 0 || quote == 1))
			quote = buf[0];
		else if (quote != 0 && buf[0] == quote)
			quote = 1;
		g_global.cmd = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = ft_strdup(g_global.cmd);
		free(g_global.cmd);
	}
	g_global.cmd = front_strtrim(tmp);
	if (ft_strncmp(g_global.cmd, "\n", 2) == 0)
	{
		free(g_global.cmd);
		g_global.cmd = ft_strdup("");
	}
	free(tmp);
	return (quote);
}

void	shell_prompt(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_putstr_fd(find_env_value(g_lstenv, "USER"), 1);
	ft_putchar_fd('@', 1);
	ft_putstr_fd("minishell:", 1);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("$ ", 1);
}

int		main(int argc, char *argv[], char **envp)
{
	char	quote;

	argc = 0;
	argv = NULL;

	init_lst(envp);
	while (1)
	{
		shell_prompt();
		quote = get_cmd();
		if (quote != 0)
			quote_cmd(quote);
		else if (g_global.cmd[0])
			many_cmd();
	}

	//while(g_lstenv != NULL)
	//{
	//		t_lst *next = g_lstenv->next;
	//		free(g_lstenv->name);
	//		free(g_lstenv->value);
	//		free(g_lstenv);
	//		g_lstenv = next;
	//}
	//free(g_lstenv);

	//free(g_lstexport);
	//while(1) ;

	return 0;
}
