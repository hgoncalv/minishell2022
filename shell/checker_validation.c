#include "../minishell.h"

void	ft_validate_pipe(char *line, int i)
{
	//NEED TO IMPLEMENT BETTER
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
		else if ((line[i + 1] == '<' || line[i + 1] == '|'))
				g_envp.valid_input = false;
	}
	else
		g_envp.valid_input = false;
	if (g_envp.valid_input == false)
		printf("FOUND ERROR @ %c\n", line[i]);
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
	if (g_envp.valid_input == false)
		printf("FOUND ERROR @ %c\n", line[i]);

}

void	ft_checker(char *line)
{
	int i = 0;

	while(line[i])
	{
		//if quotes jump to next quote
		if (line[i] == '|')
			ft_validate_pipe(line, i);
		if (line[i] == '>')
			ft_validate_redir_output(line, i);
		if (line[i] == '<')
			ft_validate_redir_input(line, i);
		printf("%c-", line[i]);
		i++;
	}
	printf("\n");
}