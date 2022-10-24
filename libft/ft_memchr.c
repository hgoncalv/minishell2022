/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:29:26 by mda-cruz          #+#    #+#             */
/*   Updated: 2021/03/10 15:51:38 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*str1;
	size_t			i;
	unsigned char	c2;

	str1 = (unsigned char *)str;
	i = 0;
	c2 = (unsigned char)c;
	while (i < n)
	{
		if (str1[i] == c2)
			return (&str1[i]);
		i++;
	}
	return (0);
}
