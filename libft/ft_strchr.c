/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 22:05:47 by mda-cruz          #+#    #+#             */
/*   Updated: 2021/03/10 15:52:21 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	c2;

	i = 0;
	c2 = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == c2)
			return ((char *)s + i);
		i++;
	}
	if (c2 == 0)
		return ((char *)s + i);
	return (0);
}
