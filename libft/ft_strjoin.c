/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 23:23:27 by jinkim            #+#    #+#             */
/*   Updated: 2020/04/09 22:22:12 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*sec_str(int i, int len, char *rtn, char *str2)
{
	int len2;

	len2 = ft_strlen(str2);
	while (i - len < len2)
	{
		rtn[i] = *str2;
		str2++;
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	char	*rtn;
	char	*str1;
	char	*str2;

	str1 = (char *)s1;
	str2 = (char *)s2;
	len = ft_strlen(str1) + ft_strlen(str2);
	rtn = (char *)malloc(sizeof(char) * (len + 1));
	if (!rtn)
		return (0);
	i = 0;
	len = ft_strlen(str1);
	while (i < len)
	{
		rtn[i] = *str1;
		str1++;
		i++;
	}
	return (sec_str(i, len, rtn, str2));
}
