/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 23:44:36 by jinkim            #+#    #+#             */
/*   Updated: 2020/04/20 20:27:45 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**final_split(char const *s, char c, char **rtn, int col)
{
	int i;
	int row;

	i = 0;
	row = 0;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] == c)
		{
			if (rtn[row] == 0)
				break ;
			rtn[row][col] = '\0';
			if (i != 0 && s[i - 1] != c)
				row++;
			col = 0;
			i++;
			continue;
		}
		rtn[row][col++] = s[i++];
		if (s[i] == '\0')
			rtn[row++][col] = '\0';
	}
	rtn[row] = 0;
	return (rtn);
}

int		malloc_len(char const *s, char c, int col, int *m_len)
{
	int	i;
	int	row;

	i = 0;
	row = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			m_len[row] = col + 1;
			if (i != 0 && s[i - 1] != c)
				row++;
			col = 0;
			i++;
			continue ;
		}
		col++;
		i++;
		if (s[i] == '\0')
			m_len[row++] = col + 1;
	}
	return (row);
}

char	**rtn_malloc(char **rtn, int row, int *m_len, int i)
{
	int idx;

	rtn = (char **)malloc(sizeof(char *) * (row + 1));
	if (!rtn)
		return (0);
	i = 0;
	while (i < row)
	{
		rtn[i] = (char *)malloc(sizeof(char) * m_len[i]);
		if (!rtn[i])
		{
			idx = 0;
			while (idx < i && rtn[idx])
				free(rtn[idx++]);
			free(rtn);
			return (0);
		}
		i++;
	}
	return (rtn);
}

char	**ft_split(char const *s, char c)
{
	char	**rtn;
	int		row;
	int		m_len[ft_strlen(s) + 1];

	row = malloc_len(s, c, 0, m_len);
	rtn = NULL;
	rtn = rtn_malloc(rtn, row, m_len, 0);
	if (rtn == 0)
		return (0);
	if (row == 0)
	{
		rtn[0] = 0;
		return (rtn);
	}
	rtn[row] = 0;
	return (final_split(s, c, rtn, 0));
}
