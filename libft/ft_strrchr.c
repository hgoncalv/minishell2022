/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 23:45:58 by mda-cruz          #+#    #+#             */
/*   Updated: 2021/03/10 15:54:14 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	c2;

	i = ft_strlen(s);
	c2 = (unsigned char)c;
	while (i >= 0)
	{
		if (s[i] == c2)
			return ((char *)s + i);
		i--;
	}
	if (c2 == 0)
		return ((char *)s + i);
	return (NULL);
}
