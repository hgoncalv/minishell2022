/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:12:43 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/10/06 22:38:10 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	res;

	i = 0;
	while (dst[i])
		i++;
	j = 0;
	while (src[j])
		j++;
	if (size <= i)
		res = (j + size);
	else
		res = (j + i);
	j = 0;
	while (src[j] && (i + 1) < size)
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (res);
}
