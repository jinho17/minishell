/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 22:47:00 by jinkim            #+#    #+#             */
/*   Updated: 2020/04/12 22:51:23 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		find(const char *str, const char *little, size_t len, size_t i)
{
	while (*little != '\0')
	{
		if (i >= len)
			return (0);
		if (*str != *little)
			return (0);
		str++;
		little++;
		i++;
	}
	return (1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*rtn;

	if (*big == '\0' && *little == '\0')
		return ((char *)big);
	if (*little == '\0' && len == 0)
		return ((char *)big);
	rtn = (char *)big;
	if (!little)
		return (rtn);
	i = 0;
	while (i < len)
	{
		if (find(rtn, little, len, i) == 1)
		{
			return (rtn);
		}
		rtn++;
		i++;
		if (rtn[0] == '\0')
			break ;
	}
	return (0);
}
