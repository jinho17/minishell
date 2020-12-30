/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 22:44:54 by jinkim            #+#    #+#             */
/*   Updated: 2020/04/06 22:44:58 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char *rtn;
	char value;

	value = (char)c;
	rtn = 0;
	while (*s)
	{
		if (*s == value)
		{
			rtn = (char *)s;
		}
		s++;
	}
	if (value == '\0')
		return ((char *)s);
	return (rtn);
}
