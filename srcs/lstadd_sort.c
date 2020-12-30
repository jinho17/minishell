/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 08:59:53 by jinkim            #+#    #+#             */
/*   Updated: 2020/12/27 00:46:04 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_curr(t_lst *bef, t_lst *curr, t_lst *new)
{
	if (bef == NULL)
	{
		new->next = curr;
		g_lstexport = new;
		return ;
	}
	bef->next = new;
	new->next = curr;
	return ;
}

void	lst_sort(t_lst *bef, t_lst *curr, t_lst *new, int len)
{
	while (1)
	{
		if (ft_strncmp(curr->name, new->name, len) > 0)
		{
			new_curr(bef, curr, new);
			break ;
		}
		else if (ft_strncmp(curr->name, new->name, len) == 0)
		{
			free(curr->value);
			curr->value = new->value;
			break ;
		}
		if (curr->next == NULL)
		{
			curr->next = new;
			break ;
		}
		bef = curr;
		curr = curr->next;
	}
}

void	lstadd_sort(t_lst **lst, char *name, char *value)
{
	t_lst	*curr;
	t_lst	*new;
	t_lst	*bef;
	int		len;

	new = lst_new(name, value);
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	bef = NULL;
	if (ft_strlen(curr->name) < ft_strlen(new->name))
		len = (int)ft_strlen(new->name);
	else
		len = (int)ft_strlen(curr->name);
	lst_sort(bef, curr, new, len);
}
