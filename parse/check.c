/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:20:43 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/11 19:20:43 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_chk_n_exit_if_null_ppchar(char **matrix, char *error_str)
{
	if (matrix == NULL)
	{
		if (error_str == NULL)
			perror("Allocation ERROR");
		else
			perror(error_str);
		exit(EXIT_FAILURE);
	}
}

void	ft_chk_n_exit_if_null_pchar(char *str, char *error_str)
{
	if (str == NULL)
	{
		if (error_str == NULL)
			perror("Allocation ERROR");
		else
			perror(error_str);
		exit(EXIT_FAILURE);
	}
}
