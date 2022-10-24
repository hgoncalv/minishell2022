/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <user@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:21:00 by mda-cruz          #+#    #+#             */
/*   Updated: 2021/03/03 17:20:39 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*str1;
	unsigned const char	*str2;

	str1 = (unsigned char *)dst;
	str2 = (unsigned const char *)src;
	i = 0;
	while (i < n)
	{
		str1[i] = str2[i];
		if (str2[i] == ((unsigned char)c))
			return (&str1[i + 1]);
		i++;
	}
	return (0);
}
