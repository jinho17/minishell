/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_change.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 00:17:42 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/18 13:28:47 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_file(char *path, char *tmp, struct stat st)
{
	if (S_ISREG(st.st_mode) != 0)
	{
		free(g_global.cmd_argv[0]);
		g_global.cmd_argv[0] = ft_strdup(tmp);
		free(path);
	}
	free(tmp);
}

char	*path_malloc(int *path_i, int len)
{
	char *path;

	*path_i = 0;
	path = (char *)malloc(sizeof(char) * len);
	return (path);
}

char	*eof_path(char *path, int *path_i)
{
	char	*rtn;

	path[*path_i] = '/';
	*path_i += 1;
	path[*path_i] = 0;
	rtn = ft_strjoin(path, g_global.cmd_argv[0]);
	return (rtn);
}

int		is_path(void)
{
	int		idx;

	if (g_global.cmd_argv[0] != 0 &&
		ft_strncmp(g_global.cmd_argv[0], "echo", 5) != 0 &&
		ft_strncmp(g_global.cmd_argv[0], "cd", 3) != 0 &&
		ft_strncmp(g_global.cmd_argv[0], "pwd", 4) != 0 &&
		ft_strncmp(g_global.cmd_argv[0], "export", 7) != 0 &&
		ft_strncmp(g_global.cmd_argv[0], "unset", 6) != 0 &&
		ft_strncmp(g_global.cmd_argv[0], "env", 4) != 0 &&
		ft_strncmp(g_global.cmd_argv[0], "exit", 5) != 0)
	{
		idx = 0;
		while (g_global.cmd_argv[0][idx])
		{
			if (g_global.cmd_argv[0][idx] == '/')
				return (1);
			idx++;
		}
		return (0);
	}
	return (1);
}

void	path_change(int idx, int path_i, char *value)
{
	char		*path;
	char		*tmp;
	struct stat	st;

	if (is_path() == 0 && value != 0)
	{
		path = (char *)malloc(sizeof(char) * (ft_strlen(value) + 1));
		while (value[idx])
		{
			if (value[idx] == ':')
			{
				tmp = eof_path(path, &path_i);
				free(path);
				path = path_malloc(&path_i, ft_strlen(value) + 1);
				stat(tmp, &st);
				is_file(path, tmp, st);
				if (S_ISREG(st.st_mode) != 0)
					return ;
			}
			else
				path[path_i++] = value[idx];
			idx++;
		}
		free(path);
	}
}
