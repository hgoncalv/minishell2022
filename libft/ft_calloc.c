/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:23:23 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/10/06 22:34:50 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t	*ptr;

	ptr = malloc(num * size);
	if (ptr == 0)
		return (ptr);
	ft_bzero(ptr, num * size);
	return (ptr);
}
