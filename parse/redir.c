/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 01:03:09 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/10/21 11:39:39 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_redir(t_vars *vars, char *filename, char *chars_str)
{
	ft_matrix_free(vars->tmp_matrix);
	free(filename);
	free(vars->tmp_str);
	free(vars->tmp_str2);
	ft_matrix_free(vars->matrix2);
	vars->matrix2 = ft_split_quote_aware(vars->str, chars_str);
}

int	ft_get_back_redir_str_if_backredir(t_vars *vars, char *chars_str)
{
	char	*filename;

	if (vars->str[0] == '<')
	{
		if (vars->str[1] && vars->str[1] != '<')
		{
			vars->tmp_matrix = ft_split_quote_aware(vars->str, " ");
			filename = ft_strdup(vars->tmp_matrix[1]);
			vars->tmp_str = ft_strdup(vars->str + ft_strlen(filename) + 3);
			vars->tmp_str2 = ft_strjoin("cat ", filename);
			free(vars->str);
			if (ft_strlen(vars->tmp_str) > 0)
			{
				if (vars->tmp_matrix[2] != NULL)
					vars->str = ft_concat3(vars->tmp_str2, "|", vars->tmp_str);
				else
					vars->str = ft_concat3(vars->tmp_str2, " ", vars->tmp_str);
			}
			else
				vars->str = ft_strdup(vars->tmp_str2);
			ft_free_redir(vars, filename, chars_str);
			return (1);
		}
	}
	return (0);
}

char	*ft_get_back_redir_str(char *str, char *chars_str)
{
	t_vars	vars;

	ft_inicialize_vars(&vars);
	vars.str = ft_strdup(str);
	vars.matrix2 = ft_split_quote_aware(vars.str, chars_str);
	while ((vars.matrix2 && vars.matrix2[0] != NULL && vars.matrix2[1] != NULL)
		|| (vars.str[0] == chars_str[0] && vars.str[1]
			&& vars.str[1] != chars_str[0]))
	{
		while (ft_strchr(FT_TOK_DELIM, vars.str[vars.i]))
			vars.i++;
		vars.tmp_str = ft_strdup(vars.str + vars.i);
		ft_swap2str(&vars.str, &vars.tmp_str);
		free(vars.tmp_str);
		if (ft_get_back_redir_str_if_backredir(&vars, chars_str))
			continue ;
		vars.matrix = ft_realloc(vars.matrix, 5 * sizeof(char *));
		vars.matrix[0] = NULL;
		ft_check_if_back_redir_fill_matrix(&vars, chars_str);
		vars.matrix2 = ft_split_quote_aware(vars.str + vars.start, chars_str);
	}
	ft_matrix_free(vars.matrix2);
	return (vars.str);
}

char	*ft_add_cat_redir(char **pipes)
{
	char	*tmp_str;
	char	**matrix;
	int		i;
	char	*line;

	matrix = ft_matrix_dup(pipes, 0);
	i = -1;
	while (matrix[++i])
	{
		tmp_str = ft_get_back_redir_str(matrix[i], "<");
		free(matrix[i]);
		matrix[i] = ft_strdup(tmp_str);
		free(tmp_str);
	}
	line = ft_concat_multi(matrix, "|");
	line[ft_strlen(line)] = '\0';
	ft_matrix_free(matrix);
	return (line);
}
