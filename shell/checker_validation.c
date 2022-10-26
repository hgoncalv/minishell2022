#include "../minishell.h"

void	ft_validate_pipe(char *line, int i)
{
	if (i == 0)
		g_envp.valid_input = false;
	if (line[i + 1] && (line[i + 1] == '|'))
		g_envp.valid_input = false;
}

void	ft_validate_redir_output(char *line, int i) //>
{
	if (i == 0)
		g_envp.valid_input = false;
	if (line[i + 1])
	{
		if ((line[i + 1] == '>'))
		{
			if ((line[i + 2] && (line[i + 2] == '<' || line[i + 2] == '>')))
			{
				g_envp.valid_input = false;
			}
		}
		else if (line[i + 1] == '<')
			g_envp.valid_input = false;
	}
	else
	{
		//we have a problem because now ls>>|text.t is giving error because ls>>\0text.t is being called.
		g_envp.valid_input = false;
	}
	
}

void	ft_validate_redir_input(char *line, int i) //<
{
	if (line[i + 1])
	{
		if ((line[i + 1] == '<'))
		{
			if ((line[i + 2] && (line[i + 2] == '<' || line[i + 2] == '>')))
				g_envp.valid_input = false;
		}
		else if ((line[i + 1] == '>') || (line[i + 1] == '|'))
			g_envp.valid_input = false;
	}
	else
		g_envp.valid_input = false;
}

bool	ft_checker(char *line)
{
	int		i;
	char	c;

	i = 0;
	while (line[i])
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
		i++;
	}
	if (g_envp.valid_input == false)
		printf("INVALID USER INPUT... ERROR IN PARSING\n");
	return (g_envp.valid_input);
}
////
void	ft_validate_pipe_matrix(char **line, int i, int j)
{
	if (i == 0 && j == 0)
		g_envp.valid_input = false;
	if (line[i + 1] == 0)
		g_envp.valid_input = false;
	if (line[i + 1][0] == '|')
		g_envp.valid_input = false;
}

void	ft_validate_redir_output_matrix(char **line, int i) //>
{
	if (line[i + 1])
	{
		if ((line[i + 1][0] == '>') || (line[i + 1][0] == '<'))
		{
				g_envp.valid_input = false;
		}
	}
	else
	{
		g_envp.valid_input = false;
	}
	
}

void	ft_validate_redir_input_matrix(char **line, int i) //<
{
	if (line[i + 1])
	{
		if ((line[i + 1][0] == '>') || (line[i + 1][0] == '<'))
		{
				g_envp.valid_input = false;
		}
	}
	else
		g_envp.valid_input = false;
}


bool	validate_the_matrix(char **matrix)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (matrix[i])
	{
		j = -1;
		while(matrix[i][++j])
		{
			if (matrix[i][j] == '\"' || matrix[i][j] == '\'')
			{
				c = matrix[i][j];
				while (matrix[i][j] && matrix[i][j] != c)
					i++;
			}
			if (matrix[i][j] == '|')
				ft_validate_pipe_matrix(matrix, i, j);
			if (matrix[i][j] == '>')
				ft_validate_redir_output_matrix(matrix, i);
			if (matrix[i][j] == '<')
				ft_validate_redir_input_matrix(matrix, i);
		}
		i++;
	}
	if (g_envp.valid_input == false)
		printf("INVALID USER INPUT... ERROR IN PARSING\n");
	return (g_envp.valid_input);
}
