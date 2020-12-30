/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 23:59:02 by jinkim            #+#    #+#             */
/*   Updated: 2020/04/13 00:10:48 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_ft(int n, long long *num, int *sign, int *len)
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

void	itoa_ft(int n, char *rtn)
{
	long long	num;
	int			i;
	int			sign;
	int			len;

	init_ft(n, &num, &sign, &len);
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
}

void	ft_putnbr_fd(int n, int fd)
{
	char	num[12];
	int		i;

	itoa_ft(n, num);
	i = 0;
	while (num[i])
	{
		write(fd, &(num[i]), 1);
		i++;
	}
}
