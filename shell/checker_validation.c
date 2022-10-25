#include "../minishell.h"

void	ft_validate_pipe(char *line, int i)
{
	if (i == 0)
		g_envp.valid_input = false;
	if (line[i + 1] && (line[i + 1] == '|' || line[i + 1] == '>'  || line[i + 1] == '<' ))
	{
		g_envp.valid_input = false;
	}
}

void	ft_validate_redir_output(char *line, int i) //>
{
	if (i == 0)
		g_envp.valid_input = false;
	if (line[i + 1])
	{
		if ((line[i + 1] == '>'))
		{
			if ((line[i + 2] && (line[i + 2] == '<' || line[i + 2] == '>' || line[i + 2] == '|' )))
				g_envp.valid_input = false;
		}
		else if (line[i + 1] == '<' )
				g_envp.valid_input = false;
	}
	else
		g_envp.valid_input = false;

}

void	ft_validate_redir_input(char *line, int i) //<
{
	if (i == 0 && line[i] && (line[i + 1] != line[i]))
		g_envp.valid_input = false;
	if (line[i + 1])
	{
		if ((line[i + 1] == '<'))
		{
			if ((line[i + 2] && (line[i + 2] == '<' || line[i + 2] == '>')))
				g_envp.valid_input = false;
		}
		else if ((line[i + 1] == '>'))
				g_envp.valid_input = false;
	}
	else
		g_envp.valid_input = false;
}

bool		ft_checker(char *line)
{
	int 	i;
	char	c;

	i = 0;
	while(line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			c = line[i];
			while (line[i] && line[i] != c)
				i++;
		}
		if (line[i] == '|')
			ft_validate_pipe(line, i);
		if (line[i] == '>')
			ft_validate_redir_output(line, i);
		if (line[i] == '<')
			ft_validate_redir_input(line, i);
		// printf("%c-", line[i]);
		i++;
	}
	printf("\n");
	if (g_envp.valid_input == false)
		printf("INVALID USER INPUT... ERROR IN PARSING\n");
	return (g_envp.valid_input);
}