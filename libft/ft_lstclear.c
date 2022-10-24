/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 17:22:52 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/10/06 22:29:44 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void
*))
{
	t_list	*lsst;

	lsst = *lst;
	if (lst)
	{
		while (*lst)
		{
			lsst = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = lsst;
		}
	}
}
