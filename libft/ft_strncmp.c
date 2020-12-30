/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 22:49:30 by jinkim            #+#    #+#             */
/*   Updated: 2020/04/06 22:50:07 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (s1[i] == s2[i])
		{
			if ((s1[i] == '\0' && s2[i] == '\0') || i == n - 1)
				return (0);
			else if ((s1[i] == '\0' && s2[i] != '\0')
					|| (s1[i] != '\0' && s2[i] == '\0'))
			{
				break ;
			}
		}
		else
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
