/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 22:53:49 by jinkim            #+#    #+#             */
/*   Updated: 2020/04/06 22:54:10 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int sign;
	int dec;

	while (*nptr == '\n' || *nptr == '\t' || *nptr == ' '
		|| *nptr == '\v' || *nptr == '\r' || *nptr == '\f')
		nptr++;
	sign = 1;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	dec = 0;
	while (*nptr)
	{
		if (*nptr < '0' || *nptr > '9')
			break ;
		dec = *nptr - '0' + dec * 10;
		nptr++;
	}
	return (dec * sign);
}
