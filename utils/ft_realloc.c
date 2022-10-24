/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:19:25 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/16 16:00:47 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (!size)
		return (ptr);
	new_ptr = malloc(size);
	if (new_ptr == NULL)
	{
		perror("malloc failed!");
		exit(EXIT_FAILURE);
	}
	ft_memset(new_ptr, 0, size);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}
