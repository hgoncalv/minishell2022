/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 09:17:37 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/10/23 23:28:30 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_is_the_end(int end, int status)
{
	if (end)
		exit(status / 256);
}

void	ft_help_pipe(t_vars val, char ***matrix, char ***cmd)
{
	pid_t	pid;
	int		status;

	matrix = ft_realloc(matrix, sizeof(char **) * (1 + val.j));
	val.i = 0;
	while (cmd[val.start] != NULL)
		matrix[val.i++] = ft_matrix_dup(cmd[val.start++], 0);
	matrix[val.i] = NULL;
	val.start = val.j - val.i;
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		ft_exec_pipe(matrix, 1);
	else
		waitpid(pid, &status, WUNTRACED);
	ft_free_cmd(matrix);
}

void	check_and_act_if_cmd_doesnotexit(t_vars *val, char **matrix)
{
	val->str = ft_get_exec_path(matrix);
	if (val->str == NULL)
	{
		write(2, "minishell: command not found: ", 30);
		write(2, matrix[0], ft_strlen(matrix[0]));
		ft_putchar_fd('\n', 2);
	}
	val->k++;
	free(val->str);
}

int	ft_setup_pipes(char ***cmd)
{
	int		status;
	t_vars	val;

	ft_inicialize_vars(&val);
	while (cmd[val.start] != NULL)
	{
		val.start++;
		val.j++;
	}
	while (--val.start && !ft_is_cmd_a_no_input(cmd[val.start]))
		;
	status = ft_exec_pipe(cmd, 0);
	return (status);
}
