/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 23:40:14 by jinkim            #+#    #+#             */
/*   Updated: 2020/04/12 22:09:46 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		head_tail(char const *s1, char const *set, int tail)
{
	int i;
	int rtn_idx;

	rtn_idx = 0;
	if (tail != -1)
		rtn_idx = tail;
	while (s1[rtn_idx] && rtn_idx >= 0)
	{
		i = 0;
		while (set[i])
		{
			if (s1[rtn_idx] == set[i])
				break ;
			i++;
		}
		if (i == (int)ft_strlen(set))
			break ;
		if (tail == -1)
			rtn_idx++;
		else
			rtn_idx--;
		if (rtn_idx == 0)
			break ;
	}
	return (rtn_idx);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*rtn;
	int		head;
	int		tail;
	int		i;

	head = head_tail(s1, set, -1);
	tail = head_tail(s1, set, (int)ft_strlen(s1) - 1);
	i = tail - head + 2;
	if (tail - head + 2 <= 0)
		i = 1;
	rtn = (char *)malloc(sizeof(char) * i);
	if (!rtn)
		return (0);
	i = 0;
	while (i < tail - head + 1)
	{
		rtn[i] = s1[head + i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}
