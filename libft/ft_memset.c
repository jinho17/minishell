/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 21:12:38 by jinkim            #+#    #+#             */
/*   Updated: 2020/04/06 22:36:28 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	v;
	size_t			i;
	char			*rtn;

	v = (unsigned char)value;
	rtn = (char *)ptr;
	i = 0;
	while (i < num)
	{
		*rtn = v;
		rtn++;
		i++;
	}
	return (ptr);
}
