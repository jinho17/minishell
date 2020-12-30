/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 21:30:11 by jinkim            #+#    #+#             */
/*   Updated: 2020/04/08 02:53:13 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && i < size - 1 && size > 0)
	{
		if (i == size - 1)
			dest[i] = '\0';
		else
			dest[i] = src[i];
		i++;
	}
	if (size != 0)
		dest[i] = '\0';
	if (i > size)
		return (i);
	else
		return (ft_strlen(src));
}
