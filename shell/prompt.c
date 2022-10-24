/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:20:27 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/20 01:04:39 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_argv(char *line)
{
	if (ft_closed_quotes(line))
	{
		printf("minishell: unclosed quote\n");
		return (0);
	}
	else if (ft_pipe_end(line))
	{
		printf("minishell: parse error near '|'\n");
		return (0);
	}
	return (1);
}

char	*ft_get_line_n_set_shell_prompt(void)
{
	char	*line;

	line = readline("minishell $ ");
	if (line == NULL)
		return (NULL);
	if (ft_strlen(line) > 0)
		add_history(line);
	return (line);
}
