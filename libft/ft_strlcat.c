/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 22:40:45 by jinkim            #+#    #+#             */
/*   Updated: 2020/04/06 22:40:46 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;
	size_t	destlen;
	char	*s;

	s = (char *)src;
	srclen = ft_strlen(s);
	destlen = ft_strlen(dest);
	i = 0;
	if (size == 0 || (destlen + 1 > size))
		return (srclen + size);
	else if (destlen + 1 == size)
		return (srclen + destlen);
	while (i < size - 1)
	{
		if (destlen <= i)
		{
			if (s[i - destlen] == 0)
				break ;
			dest[i] = s[i - destlen];
		}
		i++;
	}
	dest[i] = '\0';
	return (srclen + destlen);
}
