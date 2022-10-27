/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 00:48:31 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/10/26 22:57:33 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredoc(char **argv)
{
	char	*line;
	char	*tmp_str;
	char	*tmp_str2;

	//void)argv;
	line = NULL;
	tmp_str = NULL;
	while (1)
	{
		tmp_str = readline("> ");
		if (line == NULL)
			line = ft_strdup(tmp_str);
		else
		{
			tmp_str2 = line;
			line = ft_concat3(line, "\n", tmp_str);
			free(tmp_str2);
		}
		free(tmp_str);
		print_arrays(argv);
		if (line[ft_strlen(line) - 1] == argv[1][0])
			break ;
	}
	printf("%s", line);
	free(line);
	return (0);
}
