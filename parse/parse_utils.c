/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:21:12 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/25 23:15:44 by hgoncalv         ###   ########.fr       */
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

int	check_cmds_for_redir_errors(char ***cmd)
{
	char	*tmp_line;
	int		i;

	i = 0;
	while (cmd[i] != NULL)
	{
		tmp_line = ft_concat_multi(cmd[i], NULL);
		if (!ft_checker(tmp_line))
		{
			free(tmp_line);
			return (0);
		}
		free(tmp_line);
		i++;
	}
	return (1);
}
