/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:19:18 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/23 17:15:00 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_inicialize_vars(t_vars *vars)
{
	vars->i = 0;
	vars->j = 0;
	vars->k = 0;
	vars->l = 0;
	vars->m = 0;
	vars->start = 0;
	vars->end = 0;
	vars->size = 0;
	vars->inner_quote = 0;
	vars->outer_quote = 0;
	vars->str = NULL;
	vars->str2 = NULL;
	vars->tmp_str = NULL;
	vars->tmp_str2 = NULL;
	vars->matrix = NULL;
	vars->matrix2 = NULL;
	vars->tmp_matrix = NULL;
	vars->tmp_matrix2 = NULL;
	vars->p2p2p = NULL;
}

void	ft_inicialize_builtins(t_builtin *builtins)
{
	builtins->num_functions = 9;
	builtins->builtin_func[0] = &ft_cd;
	builtins->builtin_func[1] = &ft_export;
	builtins->builtin_func[2] = &ft_unset;
	builtins->builtin_func[3] = &ft_exit;
	builtins->builtin_func[4] = &ft_pwd;
	builtins->builtin_func[5] = &ft_env;
	builtins->builtin_func[6] = &ft_echo;
	builtins->builtin_func[7] = &ft_help;
	builtins->builtin_func[8] = &ft_heredoc;
	builtins->builtin_str[0] = "cd";
	builtins->builtin_str[1] = "export";
	builtins->builtin_str[2] = "unset";
	builtins->builtin_str[3] = "exit";
	builtins->builtin_str[4] = "pwd";
	builtins->builtin_str[5] = "env";
	builtins->builtin_str[6] = "echo";
	builtins->builtin_str[8] = "ft_heredoc";
	builtins->builtin_str[7] = "help";
}

t_values	ft_init_values(t_values value)
{
	value.quote = 0;
	value.start = 0;
	value.j = 0;
	value.i = 0;
	return (value);
}
