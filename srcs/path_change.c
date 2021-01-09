/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_change.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 00:17:42 by jinkim            #+#    #+#             */
/*   Updated: 2021/01/09 00:25:33 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_path(void)
{
	char	*tmp;

	tmp = ft_substr(g_global.cmd_argv[0], 0, 5);
	if (ft_strncmp(tmp, "/bin/", 6) == 0)
	{
		free(tmp);
		tmp = ft_substr(g_global.cmd_argv[0], 5, ft_strlen(g_global.cmd_argv[0]));
		free(g_global.cmd_argv[0]);
		g_global.cmd_argv[0] = ft_strdup(tmp);
	}
	free(tmp);
}
