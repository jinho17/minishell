/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 08:38:09 by jinkim            #+#    #+#             */
/*   Updated: 2020/12/27 21:33:33 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*lst_new(char *name, char *value)
{
	t_lst	*head;

	head = (t_lst *)malloc(sizeof(t_lst));
	head->name = ft_strdup(name);
	head->value = ft_strdup(value);
	head->next = 0;
	free(name);
	free(value);
	return (head);
}

t_lst	*lstlast(t_lst *lst)
{
	t_lst	*tmp;

	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	lstadd_back(t_lst **lst, char *name, char *value)
{
	t_lst	*last;
	t_lst	*new;

	new = lst_new(name, value);
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = lstlast(*lst);
	last->next = new;
}

void	init_lst(char **envp)
{
	int		idx;
	char	*name;
	char	*value;

	name = get_env_name(envp[0]);
	value = get_env_value(envp[0]);
	g_lstenv = lst_new(name, value);
	idx = 1;
	while (envp[idx] != 0)
	{
		name = get_env_name(envp[idx]);
		value = get_env_value(envp[idx++]);
		lstadd_back(&g_lstenv, name, value);
	}
	name = get_env_name(envp[0]);
	value = get_env_value(envp[0]);
	g_lstexport = lst_new(name, value);
	idx = 1;
	while (envp[idx] != 0)
	{
		name = get_env_name(envp[idx]);
		value = get_env_value(envp[idx++]);
		lstadd_sort(&g_lstexport, name, value);
	}
}
