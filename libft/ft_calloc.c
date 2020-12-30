/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 23:13:10 by jinkim            #+#    #+#             */
/*   Updated: 2020/04/06 23:13:13 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void *rtn;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	rtn = malloc(nmemb * size);
	if (rtn)
		ft_bzero(rtn, nmemb * size);
	return (rtn);
}
