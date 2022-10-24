/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:21:12 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/20 01:06:15 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_split_quote_aware(char *str, char *chars2split)
{
	t_vars	vars;

	ft_inicialize_vars(&vars);
	vars.tmp_matrix2 = ft_split_line(str, chars2split);
	vars.tmp_matrix = ft_tokenized_str2_matrix(vars.tmp_matrix2);
	free(vars.tmp_matrix2);
	return (vars.tmp_matrix);
}
