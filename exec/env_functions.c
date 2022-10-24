/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:22:22 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/23 21:27:25 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_setenv(char *name, char *value, int overwrite)
{
	int		i;
	char	*str;

	i = -1;
	if (value == NULL)
		str = ft_strjoin(name, "=");
	else
		str = ft_concat3(name, "=", value);
	if (str == NULL)
		return (0);
	while (g_envp.envp[++i] != NULL && name && ft_strncmp(g_envp.envp[i], name,
			ft_strlen(name)))
		;
	if (g_envp.envp[i] != NULL && overwrite == 1)
	{
		free(g_envp.envp[i]);
		g_envp.envp[i] = ft_strdup(str);
	}
	else if (g_envp.envp[i] == NULL)
		g_envp.envp = ft_matrix_push(g_envp.envp, str);
	free(str);
	return (1);
}

char	*ft_getenv(char *name, int trimmed)
{
	int		i;
	char	**split;
	char	*ret;

	i = -1;
	while (g_envp.envp[++i] != NULL && name && ft_strncmp(g_envp.envp[i], name,
			ft_strlen(name)))
		;
	if (g_envp.envp[i] != NULL)
	{
		split = ft_split(g_envp.envp[i], '=');
		if (split[1] == NULL)
			ret = NULL;
		else if (!trimmed)
			ret = ft_concat_string_between_chars(2, split[1], 3);
		else
			ret = ft_strdup(split[1]);
		ft_matrix_free(split);
		return (ret);
	}
	return (NULL);
}

void	ft_export_no_args(void)
{
	t_vars	vars;

	ft_inicialize_vars(&vars);
	vars.matrix = ft_matrix_dup(g_envp.envp, 0);
	while (vars.matrix[vars.l] != NULL)
	{
		while (vars.matrix[vars.k + 1] != NULL)
		{
			vars.i = ft_strlen(vars.matrix[vars.k]);
			vars.j = ft_strlen(vars.matrix[vars.k + 1]);
			if (vars.i > vars.j)
				vars.i = vars.j;
			if (ft_strncmp(vars.matrix[vars.k], vars.matrix[vars.k + 1],
					vars.i) > 0)
				ft_swap2str(&(vars.matrix[vars.k]), &(vars.matrix[vars.k + 1]));
			vars.k++;
		}
		vars.k = 0;
		vars.l++;
	}
	ft_print_matrix_add_str2line_start(vars.matrix, "declare -x", " ");
	ft_matrix_free(vars.matrix);
}

int	ft_export(char **argv)
{
	t_vars	vars;

	ft_inicialize_vars(&vars);
	if (argv[1] && argv[1][0] != '#')
	{
		vars.matrix = ft_split(argv[1], '=');
		if (vars.matrix[0] && !is_valid_env_var_name(vars.matrix))
			return (1);
		else
		{
			if (vars.matrix[1])
				ft_setenv(vars.matrix[0], vars.matrix[1], 1);
			else
				ft_setenv(vars.matrix[0], NULL, 1);
			ft_matrix_free(vars.matrix);
			if (argv[2])
			{
				printf("minishell: export : one var at a time\n");
				return (0);
			}
		}
	}
	else
		ft_export_no_args();
	return (0);
}

int	ft_unset(char **argv)
{
	int	i;

	if (argv[1] == NULL)
		return (0);
	i = -1;
	while (g_envp.envp[++i] != NULL && ft_strncmp(g_envp.envp[i], argv[1],
			ft_strlen(argv[1])))
		;
	if (g_envp.envp[i] != NULL)
		g_envp.envp = ft_matrix_remove_col_by_index(g_envp.envp, i);
	return (0);
}
