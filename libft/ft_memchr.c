/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 21:24:23 by jinkim            #+#    #+#             */
/*   Updated: 2020/04/06 22:35:50 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	value;

	str = (unsigned char *)s;
	i = 0;
	value = (unsigned char)c;
	while (i < n)
	{
		if (*str == value)
		{
			return (str);
		}
		str++;
		i++;
	}
	return (0);
}
