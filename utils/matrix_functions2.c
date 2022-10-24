/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:19:07 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/19 13:07:28 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_matrix_add_str2line_start(char **matrix, char *str, char *glue)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		if (matrix[i][0] == '?' && matrix[i][1] == '=')
		{
			i++;
			continue ;
		}
		ft_putstr_fd(str, 1);
		if (glue != NULL)
			ft_putstr_fd(glue, 1);
		ft_putstr_fd(matrix[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return ;
}

void	ft_swap2str(char **str1, char **str2)
{
	char	*tmp_str;

	tmp_str = ft_strdup(*str1);
	free(*str1);
	*str1 = ft_strdup(*str2);
	free(*str2);
	*str2 = ft_strdup(tmp_str);
	free(tmp_str);
}
