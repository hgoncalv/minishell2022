/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:21:28 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/20 12:42:57 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
   @brief Builtin command: print help.
   @param argv List of argv.  Not examined.
   @return Always returns 1, to continue executing.
 */

int	ft_help(char **argv)
{
	int			i;
	t_builtin	builtins;

	ft_inicialize_builtins(&builtins);
	(void)argv;
	i = 0;
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");
	while (i < builtins.num_functions)
	{
		printf("  %s\n", builtins.builtin_str[i++]);
	}
	printf("Use the man command for information on other programs.\n");
	return (1);
}

int	ft_set_cd_folder_return_if_free_folder_or_not(char **argv,
												char **ptr2folder)
{
	char	*tmp_str;
	int		to_free;

	to_free = 1;
	if (argv[1] == NULL)
		*ptr2folder = ft_getenv("HOME", 1);
	else if (argv[1][0] == '-')
		*ptr2folder = ft_getenv("OLDPWD", 1);
	else if (argv[1][0] == '~')
	{
		tmp_str = ft_getenv("HOME", 1);
		*ptr2folder = ft_strjoin(tmp_str, argv[1] + 1);
		free(tmp_str);
	}
	else
	{
		*ptr2folder = argv[1];
		to_free = 0;
	}
	return (to_free);
}
