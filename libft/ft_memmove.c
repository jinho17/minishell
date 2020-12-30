/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 21:23:24 by jinkim            #+#    #+#             */
/*   Updated: 2020/04/06 22:36:20 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;
	char	buf[n];
	size_t	i;

	s = (char *)src;
	d = (char *)dest;
	i = 0;
	while (i < n)
	{
		buf[i++] = *s++;
	}
	i = 0;
	while (i < n)
	{
		*d = buf[i];
		d++;
		i++;
	}
	return (dest);
}
