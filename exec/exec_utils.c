/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:22:06 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/22 12:37:12 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_exec_path_chk_access(char *path, char **env_path, char ***matrix)
{
	if (access(path, F_OK) != -1)
	{
		free(*env_path);
		free(*matrix);
		return (1);
	}
	return (0);
}

char	*ft_get_exec_path(char **argv)
{
	char	*env_path;
	char	*path;
	t_vars	vars;

	ft_inicialize_vars(&vars);
	if (access(argv[0], F_OK) != -1)
		return (argv[0]);
	vars.tmp_str = ft_getenv("PATH", 1);
	if (!vars.tmp_str)
		return (NULL);
	env_path = ft_strdup(vars.tmp_str);
	free(vars.tmp_str);
	vars.matrix = ft_split_line(env_path, ":");
	while (vars.matrix[vars.i] != NULL)
	{
		path = ft_concat3(vars.matrix[vars.i], "/", argv[0]);
		if (ft_get_exec_path_chk_access(path, &env_path, &(vars.matrix)))
			return (path);
		free(path);
		(vars.i)++;
	}
	free(env_path);
	free(vars.matrix);
	return (NULL);
}

char	**ft_tokenized_str2_matrix(char **cmd)
{
	char	**argv;
	t_vars	vars;

	argv = NULL;
	ft_inicialize_vars(&vars);
	while (cmd[vars.i])
		(vars.i)++;
	argv = ft_realloc(argv, (vars.i + 1) * sizeof(char *));
	while (cmd[vars.j])
	{
		argv[vars.j] = ft_strdup(cmd[vars.j]);
		(vars.j)++;
	}
	argv[vars.j] = NULL;
	return (argv);
}

char	**ft_args_matrix(char **cmd, char **argv)
{
	char	*tmp_str;

	if (cmd[0][0] == '<' && cmd[0][1] == '<')
	{
		tmp_str = ft_strdup(cmd[0]);
		ft_matrix_free(argv);
		argv = malloc(3 * sizeof(char *));
		argv[0] = ft_strdup("ft_heredoc");
		argv[1] = ft_strdup(tmp_str + 2);
		argv[2] = NULL;
		free(tmp_str);
	}
	return (argv);
}

char	**ft_tokenized_str2_matrix_remove_nps(char **cmd)
{
	char	**argv;
	t_vars	vars;
	char	chars2remove[3];

	argv = NULL;
	chars2remove[0] = 2;
	chars2remove[1] = 3;
	chars2remove[2] = '\0';
	ft_inicialize_vars(&vars);
	while (cmd[vars.i])
		(vars.i)++;
	argv = ft_realloc(argv, (vars.i + 1) * sizeof(char *));
	while (cmd[vars.j])
	{
		argv[vars.j] = ft_strdup(cmd[vars.j]);
		argv[vars.j] = ft_remove_chars(argv[vars.j], chars2remove, 1);
		(vars.j)++;
	}
	argv[vars.j] = NULL;
	return (argv);
}
