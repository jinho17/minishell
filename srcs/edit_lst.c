/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 23:35:13 by jinkim            #+#    #+#             */
/*   Updated: 2020/12/27 00:53:48 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ch_env_value(t_lst *lst, char *name, char *value)
{
	int		idx;
	t_lst	*curr;

	idx = 0;
	curr = lst;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->name, name, ft_strlen(name) + 1) == 0)
		{
			curr->value = value;
			break ;
		}
		curr = curr->next;
	}
}

void	add_lstenv(char *name, char *value)
{
	t_lst	*bef_last;
	t_lst	*new;

	if (find_env_value(g_lstenv, name) == NULL)
	{
		bef_last = lst_beforelast(g_lstenv);
		new = lst_new(name, value);
		new->next = bef_last->next;
		bef_last->next = new;
	}
	else
		ch_env_value(g_lstenv, name, value);
}

t_lst	*lst_beforelast(t_lst *lst)
{
	t_lst	*tmp;
	t_lst	*bef;

	tmp = lst;
	bef = 0;
	while (tmp->next)
	{
		bef = tmp;
		tmp = tmp->next;
	}
	return (bef);
}

void	add_lstexport(char *name, char *value)
{
	int		rtn;
	char	*tmp;

	if (value[0] == 0)
	{
		free(value);
		value = ft_strdup("''");
	}
	else if ((rtn = str_equal(value)) > 0)
	{
		tmp = ft_strjoin("'", value);
		free(value);
		value = ft_strjoin(tmp, "'");
		free(tmp);
	}
	lstadd_sort(&g_lstexport, name, value);
}

void	edit_lst(char *str)
{
	char	*name;
	char	*value;

	name = get_env_name(str);
	value = get_env_value(str);
	add_lstexport(name, value);
	name = get_env_name(str);
	value = get_env_value(str);
	add_lstenv(name, value);
}
