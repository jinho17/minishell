/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dectohex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 17:00:53 by jinkim            #+#    #+#             */
/*   Updated: 2020/05/06 15:47:45 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*make_str(int len, long long d, char x, int sign)
{
	char		*rtn;
	int			i;
	long long	mod;

	rtn = (char *)malloc(sizeof(char) * (len + 1));
	i = len - 1;
	while (i >= 0)
	{
		mod = d % 16;
		if (mod <= 9)
			rtn[i--] = mod + '0';
		else
		{
			if (x == 'x')
				rtn[i--] = (mod % 10) + 'a';
			else if (x == 'X')
				rtn[i--] = (mod % 10) + 'A';
		}
		d = d / 16;
	}
	if (sign < 0)
		rtn[0] = '-';
	rtn[len] = '\0';
	return (rtn);
}

char	*ft_dectohex(long long d, char x)
{
	int			len;
	int			sign;
	long long	dec;

	len = 0;
	sign = 1;
	if (d == 0)
		len++;
	if (d < 0)
	{
		len++;
		sign = -1;
	}
	d = d * sign;
	dec = d;
	while (dec)
	{
		dec = dec / 16;
		len++;
	}
	return (make_str(len, d, x, sign));
}
