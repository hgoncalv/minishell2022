/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:21:34 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/25 23:43:10 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execute(char **cmd)
{
	int			ret;
	char		**argv;
	t_vars		vars;
	t_builtin	builtins;

	ft_inicialize_builtins(&builtins);
	ft_inicialize_vars(&vars);
	ret = -666;
	if (cmd[0] == NULL)
		return (1);
	argv = ft_check_export_return_argv(cmd);
	if (!argv)
		argv = ft_tokenized_str2_matrix_remove_nps(cmd);
	ret = ft_execute_if_builtin_run(argv, 0);
	if (ret != 666)
		return (ret);
	ret = ft_launch(argv);
	ft_matrix_free(argv);
	return (ret);
}

void	ft_launch_pid0(int *ret, char ***argv, char **path)
{
	ft_check_set_output2file(*argv, 1);
	*ret = ft_execute_if_builtin_run(*argv, 1);
	if (*ret != 666)
		exit(*ret);
	*path = ft_get_exec_path(*argv);
	if (*path == NULL)
	{
		*ret = 127;
		exit(127);
	}
	else
		*ret = execve(*path, *argv, g_envp.envp);
	if (*ret == -1)
		perror("minishel");
	free(*path);
	exit(EXIT_SUCCESS);
}

int	ft_launch(char **argv)
{
	int		status;
	int		ret;
	pid_t	pid;
	char	*path;

	ret = 2;
	pid = fork();
	if (pid == 0)
	{
		ft_launch_pid0(&ret, &argv, &path);
	}
	else if (pid < 0)
		perror("minishell");
	else
		waitpid(pid, &status, WUNTRACED);
	if (status / 256 == 127)
	{
		write(2, "minishell: command not found:", 29);
		write(2, argv[0], ft_strlen(argv[0]));
		ft_putchar_fd('\n', 2);
	}
	return (status / 256);
}

int	ft_child_proces(int *fd_in, int *p, char ***cmd)
{
	int		ret;
	char	**argv;

	argv = *(cmd);
	dup2(*fd_in, 0);
	if (*(cmd + 1) != NULL)
		dup2(p[1], 1);
	close(p[0]);
	ret = ft_execute(argv);
	exit(ret);
}

int	ft_exec_pipe(char ***cmd, int end)
{
	int			p[2];
	pid_t		pid;
	t_values	v;
	int			status;

	v = ft_init_values(v);
	while ((!end && cmd[v.i] != NULL) || (end && v.i <= end
			&& cmd[v.i] != NULL))
	{
		pipe(p);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
			ft_child_proces(&v.j, p, cmd + v.i);
		else
		{
			waitpid(pid, &status, WUNTRACED);
			close(p[1]);
			v.j = p[0];
			v.i++;
		}
	}
	ft_is_the_end(end, status);
	return (status / 256);
}
