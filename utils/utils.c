/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:18:49 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/22 21:38:05 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// We have to check if the quotes are closed
//Approved quotes : " " ; " ' "; '';
//Not approved: "; ';
int	ft_closed_quotes(char *line)
{
	int	quote;
	int	i;

	quote = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '"')
		{
			if (quote == 0)
				quote = 2;
			else if (quote == 2)
				quote = 0;
		}
		if (line[i] == '\'')
		{
			if (quote == 0)
				quote = 1;
			else if (quote == 1)
				quote = 0;
		}
	}
	if (quote > 0)
		return (1);
	return (0);
}

int	ft_is_quote(char c, int quote)
{
	if (c == '"')
	{
		if (quote == 0)
			quote = 2;
		else if (quote == 2)
			quote = 0;
	}
	else if (c == '\'')
	{
		if (quote == 0)
			quote = 1;
		else if (quote == 1)
			quote = 0;
	}
	return (quote);
}

void	ft_get_quotes_inner_outer(char c, t_vars *vars)
{
	int	num;

	num = 0;
	if (c == '"')
		num = 2;
	else if (c == '\'')
		num = 1;
	if (num != 0)
	{
		if (vars->outer_quote == 0)
			vars->outer_quote = num;
		else if (vars->outer_quote == num)
			vars->outer_quote = 0;
		else
		{
			if (vars->inner_quote == 0)
				vars->inner_quote = num;
			else if (vars->inner_quote == num)
				vars->inner_quote = 0;
		}
	}
}

int	ft_pipe_end(char *line)
{
	int	i;
	int	control;
	int	quote;

	i = -1;
	quote = 0;
	control = 0;
	while (line[++i])
	{
		quote = ft_is_quote(line[i], quote);
		if (line[i] != '|' && line[i] != ' ')
			control = 1;
		if (line[i] == '|')
		{
			if (control == 0 && quote == 0)
				return (1);
			control = 0;
		}
	}
	return (0);
}

int	ft_is_cmd_a_no_input(char **cmd)
{
	int		i;
	char	*no_input[10];

	no_input[0] = "ls";
	no_input[1] = "pwd";
	no_input[2] = "echo";
	no_input[3] = "env";
	i = 0;
	while (i < 4)
	{
		if (ft_strlen(cmd[0]) == ft_strlen(no_input[i]) && ft_strncmp(cmd[0],
				no_input[i], ft_strlen(cmd[0])) == 0)
			return (1);
		i++;
	}
	return (0);
}
