/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:19:12 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/16 16:03:49 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_matrix_get_num_col(char **matrix)
{
	int	col_num;

	col_num = -1;
	while (matrix[++col_num] != NULL)
		;
	return (col_num);
}

char	**ft_matrix_dup(char **matrix, int push)
{
	int		col_num;
	char	**list;
	int		i;

	list = NULL;
	col_num = ft_matrix_get_num_col(matrix);
	list = ft_realloc(list, (col_num + 1 + push) * sizeof(char *));
	ft_chk_n_exit_if_null_ppchar(list, NULL);
	i = -1;
	while (++i < col_num)
	{
		list[i] = ft_strdup(matrix[i]);
		ft_chk_n_exit_if_null_pchar(list[i], NULL);
	}
	list[i + push] = NULL;
	return (list);
}

char	**ft_matrix_push(char **matrix, char *str)
{
	int		col_num;
	char	**list;

	col_num = ft_matrix_get_num_col(matrix);
	list = ft_matrix_dup(matrix, 1);
	list[col_num] = ft_strdup(str);
	ft_chk_n_exit_if_null_pchar(list[col_num], NULL);
	ft_matrix_free(matrix);
	return (list);
}

void	ft_matrix_free(char **matrix)
{
	int	col_num;

	col_num = 0;
	if (matrix[0] != NULL)
	{
		while (matrix[col_num] != NULL)
		{
			free(matrix[col_num]);
			col_num++;
		}
		free(matrix[col_num]);
	}
	free(matrix);
}

char	**ft_matrix_remove_col_by_index(char **matrix, int index)
{
	int		col_num;
	char	**list;
	int		i;
	int		j;

	list = NULL;
	col_num = ft_matrix_get_num_col(matrix);
	list = ft_realloc(list, (col_num) * sizeof(char *));
	ft_chk_n_exit_if_null_ppchar(list, NULL);
	i = 0;
	j = 0;
	while (i < col_num - 1)
	{
		if (i == index)
			i++;
		list[j] = ft_strdup(matrix[i]);
		ft_chk_n_exit_if_null_pchar(list[j], NULL);
		i++;
		j++;
	}
	list[j] = NULL;
	ft_matrix_free(matrix);
	return (list);
}
