/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:03:33 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/10/21 13:25:15 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_vars	*ft_get_vars(t_vars *vars, char *chars2replace)
{
	if (chars2replace[0] == '<')
	{
		vars->matrix[0] = ft_strdup("cat ");
		vars->matrix[1] = ft_strdup(vars->matrix2[1]);
		vars->matrix[2] = ft_strdup("|");
		vars->matrix[3] = ft_strdup(vars->matrix2[0]);
		vars->matrix[4] = NULL;
	}
	if (vars->str)
		free(vars->str);
	return (vars);
}

t_vars	*ft_get_redir(t_vars *vars, char *glue, char *glue_end)
{
	glue_end = "|cat >>";
	glue = ft_concat3("|", vars->matrix2[0], glue_end);
	while (vars->matrix2[++vars->l])
	{
		if (ft_strncmp(vars->matrix2[vars->l], "cat >", 5))
			ft_putstr_fd("\ndo not touch\n", 1);
		else
		{
			vars->tmp_str = ft_strjoin(vars->matrix2[vars->l], glue);
			ft_swap2str(&(vars->tmp_str), &(vars->matrix2[vars->l]));
		}
	}
	vars->str2 = ft_concat_multi(vars->matrix2 + 1, glue);
	vars->str = ft_concat3(vars->matrix2[0], glue_end, vars->str2);
	free(vars->str2);
	free(glue);
	vars->start = ft_strlen(vars->str);
	return (vars);
}

t_vars	*ft_get_out(t_vars *vars, char *glue, char *glue_end)
{
	glue = ft_concat3("|", vars->matrix2[0], glue_end);
	while (vars->matrix2[++vars->l])
	{
		if (!ft_strncmp(vars->matrix2[vars->l], "cat", 3))
			ft_putstr_fd("\ndo not touch\n", 1);
		else
		{
			vars->tmp_str = ft_strjoin(glue,
					vars->matrix2[vars->l]);
			ft_swap2str(&(vars->tmp_str), &(vars->matrix2[vars->l]));
		}
	}
	free(vars->tmp_str);
	vars->tmp_str = ft_concat_multi(vars->matrix2 + 1, NULL);
	vars->str = ft_strdup(vars->tmp_str + 1);
	free(vars->tmp_str);
	free(glue);
	vars->start = ft_strlen(vars->str);
	return (vars);
}
