/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <user@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:42:24 by mda-cruz          #+#    #+#             */
/*   Updated: 2021/03/14 16:50:53 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*lis;

	i = 0;
	lis = lst;
	while (lis)
	{
		lis = lis->next;
		i++;
	}
	return (i);
}
