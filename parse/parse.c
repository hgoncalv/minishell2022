/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:21:06 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/27 01:05:01 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_get_token(char *token, char **tokens, char *delimiters,
		char *chars2jump)
{
	int	position;
	int	bufsize;

	bufsize = FT_TOK_BUFSIZE;
	position = 0;
	while (token != NULL)
	{
		tokens[position] = token;
		position++;
		if (position >= bufsize)
		{
			bufsize += FT_TOK_BUFSIZE;
			tokens = ft_realloc(tokens, bufsize * sizeof(char *));
			ft_chk_n_exit_if_null_ppchar(tokens, NULL);
		}
		token = ft_strtok_quote_aware(NULL, delimiters, chars2jump);
	}
	tokens[position] = NULL;
	return (tokens);
}

char	**ft_split_line(char *line, char *delimiters)
{
	int		bufsize;
	char	**tokens;
	char	*token;
	char	chars2jump[4];

	ft_memmove(chars2jump + 1, "'\"\0", 3);
	chars2jump[0] = 2;
	tokens = NULL;
	bufsize = FT_TOK_BUFSIZE;
	tokens = ft_realloc(tokens, bufsize * sizeof(char *));
	ft_chk_n_exit_if_null_ppchar(tokens, NULL);
	token = ft_strtok_quote_aware(line, delimiters, chars2jump);
	tokens = ft_get_token(token, tokens, delimiters, chars2jump);
	return (tokens);
}

void	ft_split_line2while(t_vars *vars, char *delimiters)
{
	vars->matrix[vars->i] = vars->str2;
	vars->i++;
	if (vars->i >= vars->j)
	{
		vars->j += FT_TOK_BUFSIZE;
		vars->matrix = ft_realloc(vars->matrix, vars->j * sizeof(char *));
		ft_chk_n_exit_if_null_ppchar(vars->matrix, NULL);
	}
	vars->str = ft_strtok_quote_aware(NULL, delimiters, vars->tmp_str2);
	if (vars->str != NULL)
	{
		vars->tmp_str = ft_strdup(vars->str);
		vars->str2 = ft_update_line(vars->tmp_str);
		free(vars->tmp_str);
	}
}

char	**ft_split_line2(char *line, char *delimiters)
{
	t_vars	vars;

	ft_inicialize_vars(&vars);
	vars.tmp_str2 = ft_concat_string_between_chars(2, "'", '"');
	vars.j = FT_TOK_BUFSIZE;
	vars.str2 = NULL;
	vars.matrix = ft_realloc(vars.matrix, vars.j * sizeof(char *));
	ft_chk_n_exit_if_null_ppchar(vars.matrix, NULL);
	vars.str = ft_strtok_quote_aware(line, delimiters, vars.tmp_str2);
	if (vars.str != NULL)
	{
		vars.tmp_str = ft_strdup(vars.str);
		vars.str2 = ft_update_line(vars.tmp_str);
		free(vars.tmp_str);
	}
	while (vars.str != NULL)
		ft_split_line2while(&vars, delimiters);
	free(vars.tmp_str2);
	vars.matrix[vars.i] = NULL;
	return (vars.matrix);
}

char	***ft_parse_cmds(char **pipes)
{
	char	***cmd;
	t_vars	v;

	cmd = NULL;
	ft_inicialize_vars(&v);
	while (pipes[v.l] != NULL)
		v.l++;
	cmd = ft_realloc(cmd, sizeof(char **) * (1 + v.l));
	while (pipes[v.i] != NULL)
	{
		v.tmp_str = pipes[v.i];
		if (v.i > 0)
			cmd = ft_realloc(cmd, (v.i + 2) * sizeof(char **));
		v.matrix = ft_split_line2(pipes[v.i], FT_TOK_DELIM);
		v.tmp_str2 = ft_concat_multi(v.matrix, " ");
		cmd[v.i] = the_matrix(v.tmp_str2);
		ft_matrix_free(v.matrix);
		free(v.tmp_str2);
		(v.i)++;
		v.j = 0;
	}
	cmd[v.i] = NULL;
	// for (size_t i = 0; cmd[i] != NULL; i++)
	// {
	// 	print_arrays(cmd[i]);
	// 	ft_putchar_fd('\n', 1);
	// }
	return (cmd);
}
