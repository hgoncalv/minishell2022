/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:22:27 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/23 17:30:19 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL && ft_strncmp(argv[i], "-n", 2) == 0)
		i++;
	while (argv[i] != NULL)
	{
		ft_putstr_fd(argv[i], 1);
		i++;
		if (argv[i] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (argv[1] == NULL || ft_strncmp(argv[1], "-n", 2) != 0
		|| (ft_strncmp(argv[1], "-n", 2) == 0 && argv[1][2]
		&& !ft_isalpha(argv[1][2])))
		ft_putchar_fd('\n', 1);
	return (0);
}

int	ft_env(char **argv)
{
	int	i;
	int	argc;

	argc = -1;
	while (argv[++argc])
		;
	if (argc == 1)
	{
		i = -1;
		while (g_envp.envp[++i])
		{
			if (g_envp.envp[i][0] == '?' && g_envp.envp[i][1] == '=')
				continue ;
			printf("%s\n", g_envp.envp[i]);
		}
	}
	else
		printf("env: too many arguments\n");
	return (0);
}

int	ft_cd(char **argv)
{
	char	*folder;
	int		to_free;
	char	pwd[256];
	int		ret;

	if (getcwd(pwd, sizeof(pwd)) == NULL)
		getcwd(pwd, sizeof(pwd));
	to_free = ft_set_cd_folder_return_if_free_folder_or_not(argv, &folder);
	ret = chdir(folder);
	if (ret != 0)
		perror("minishell");
	ft_setenv("OLDPWD", pwd, 1);
	if (getcwd(pwd, sizeof(pwd)) == NULL)
		perror("getcwd() error");
	ft_setenv("PWD", pwd, 1);
	if (to_free)
		free(folder);
	return (ret * (-1));
}

int	ft_pwd(char **argv)
{
	char	cwd[256];

	(void)argv;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		if (getenv("PWD") != NULL)
			printf("%s\n", getenv("PWD"));
	}
	else
		printf("%s\n", cwd);
	return (0);
}

int	ft_exit(char **argv)
{
	g_envp.to_exit = 1;
	if (argv[1])
	{
		if (ft_isnum(argv[1]))
			return (ft_atoi(argv[1]));
		else
		{
			g_envp.exit_str = ft_strdup(argv[1]);
			return (2);
		}
	}
	else
		return (0);
}
