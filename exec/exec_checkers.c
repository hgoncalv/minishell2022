/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_checkers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:22:16 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/23 17:24:48 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_check_export_return_argv(char **cmd)
{
	char	**export;
	char	**argv;

	argv = NULL;
	if (!cmd[1])
	{
		export = ft_split(cmd[0], '=');
		if (export[0] && ft_strlen(export[0]) < ft_strlen(cmd[0]))
		{
			argv = ft_realloc(argv, (3) * sizeof(char *));
			argv[0] = ft_strdup("export");
			argv[1] = ft_strdup(cmd[0]);
			argv[2] = NULL;
		}
		ft_matrix_free(export);
	}
	return (argv);
}

void	ft_check_if_back_redir_fill_matrix(t_vars *vars, char *chars2replace)
{
	char	*glue;
	char	*glue_end;

	glue = NULL;
	vars = ft_get_vars(vars, chars2replace);
	if (chars2replace[0] == '<')
		vars->str = ft_concat_multi(vars->matrix, NULL);
	else if (chars2replace[0] == '>')
	{
		glue_end = "|cat >";
		if (chars2replace[1] == '>')
			vars = ft_get_redir(vars, glue, glue_end);
		else
			vars = ft_get_out(vars, glue, glue_end);
	}
	ft_matrix_free(vars->matrix);
	ft_matrix_free(vars->matrix2);
}

int	ft_check_if_back_redirection(char **argv)
{
	char	***cmds;
	char	**pipes;
	t_vars	vars;

	ft_inicialize_vars(&vars);
	while (argv[vars.i] != NULL)
		(vars.i)++;
	vars.str = ft_concat_multi(argv, " ");
	vars.matrix2 = ft_split(vars.str, '<');
	free(vars.str);
	vars.matrix = malloc(5 * sizeof(char *));
	if (vars.matrix == NULL)
		exit(0);
	if (vars.matrix2[1] != NULL)
	{
		ft_check_if_back_redir_fill_matrix(&vars, "<");
		pipes = ft_split_line(vars.str, "|");
		cmds = ft_parse_cmds(pipes);
		vars.j = ft_exec_pipe(cmds, 0);
		free(vars.str);
		ft_free_loop(cmds, pipes, NULL);
	}
	return (vars.j);
}

int	ft_check_set_output2file(char **argv, int piped)
{
	int	output_index;
	int	fout;

	(void)piped;
	output_index = 0;
	while (argv[output_index])
	{
		if (*argv[output_index] == '>')
			break ;
		output_index++;
	}
	if (argv[output_index] && *argv[output_index] == '>')
	{
		if ((argv[output_index][1]) == '>')
			fout = open(argv[output_index + 1], O_WRONLY | O_CREAT | O_APPEND,
					0777);
		else
			fout = open(argv[output_index + 1], O_WRONLY | O_CREAT | O_TRUNC,
					0777);
		argv[output_index] = NULL;
		dup2(fout, STDOUT_FILENO);
		close(fout);
	}
	return (1);
}
