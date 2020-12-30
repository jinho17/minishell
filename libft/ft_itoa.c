/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 23:46:42 by jinkim            #+#    #+#             */
/*   Updated: 2020/05/07 18:50:40 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init(int n, long long *num, int *sign, int *len)
{
	*num = n;
	*len = 0;
	*sign = 1;
	if (*num < 0)
	{
		*len = *len + 1;
		*sign = -1;
		*num = *sign * *num;
	}
	while (*num != 0)
	{
		*num = *num / 10;
		*len = *len + 1;
	}
	if (n == 0)
		*len = 1;
}

char	*ft_itoa(int n)
{
	char		*rtn;
	long long	num;
	int			i;
	int			sign;
	int			len;

	init(n, &num, &sign, &len);
	rtn = (char *)malloc(sizeof(char) * (len + 1));
	if (!rtn)
		return (0);
	if (n == 0)
		rtn[0] = '0';
	if (sign == -1)
		rtn[0] = '-';
	num = n;
	num = sign * num;
	i = len - 1;
	while (num != 0)
	{
		rtn[i] = num % 10 + '0';
		num = num / 10;
		i--;
	}
	rtn[len] = '\0';
	return (rtn);
}
