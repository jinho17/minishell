/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 09:32:26 by jinkim            #+#    #+#             */
/*   Updated: 2020/12/27 22:51:25 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env_value(t_lst *lst, char *name)
{
	int		idx;
	t_lst	*curr;

	idx = 0;
	curr = lst;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->name, name, ft_strlen(name) + 1) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

char	*get_env_value(char *str)
{
	char	*value;
	int		i;

	i = 0;
	while (str[i] != '=' && str[i] != 0)
		i++;
	if (i == (int)ft_strlen(str))
		value = ft_strdup("");
	else
		value = ft_substr(str, i + 1, (int)ft_strlen(str));
	return (value);
}

char	*get_env_name(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] != '=' && str[i] != 0)
		i++;
	name = ft_substr(str, 0, i);
	return (name);
}
