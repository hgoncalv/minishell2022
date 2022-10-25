/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:20:19 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/24 00:55:37 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envp	g_envp;

void	ft_set_env_cmd_return(int status)
{
	char	*status_str;

	status_str = ft_itoa(status);
	ft_setenv("?", status_str, 1);
	free(status_str);
}

char	***ft_get_cmds(char **line, char ***pipes)
{
	char	***cmd;

	*line = ft_var_expansion(*line);
	*pipes = ft_split_line(*line, "|");
	cmd = ft_parse_cmds(*pipes);
	return (cmd);
}


void	ft_loop_confirmed(char ****cmd, char ***pipes, int *status, char **line)
{
	*cmd = ft_get_cmds(line, pipes);
	if ((*pipes)[0] && (*pipes)[1] == NULL)
		*status = ft_execute((*cmd)[0]);
	else if (*pipes[0])
		*status = ft_setup_pipes(*cmd);
	ft_set_env_cmd_return(*status);
	ft_free_loop(*cmd, *pipes, *line);
}

int	ft_loop(void)
{
	char	***cmd;
	char	**pipes;
	int		status;
	char	*line;

	status = 0;
	while (g_envp.to_exit == 0)
	{
		g_envp.valid_input = true;
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, SIG_IGN);
		line = ft_get_line_n_set_shell_prompt();
		if (line == NULL)
			break ;
		if (!ft_checker(line))
		{
			free(line);
			continue ;
		}
		if (ft_check_argv(line))
			ft_loop_confirmed(&cmd, &pipes, &status, &line);
		else
			free(line);
	}
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	char	**shell_envp;
	int		status;

	status = 0;
	shell_envp = ft_matrix_dup(envp, 0);
	g_envp.envp = shell_envp;
	g_envp.to_exit = 0;
	g_envp.exit_str = NULL;
	g_envp.valid_input = true;
	ft_set_env_cmd_return(0);
	(void)argc;
	(void)argv;
	status = ft_loop();
	if (g_envp.exit_str == NULL)
	{
		ft_matrix_free(g_envp.envp);
		return (status);
	}
	else
	{
		printf("minishell: exit: %s: numeric argument required\n",
			g_envp.exit_str);
		return (2);
	}
	return (status);
}
