/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cond.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:22:11 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/23 22:56:05 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execute_if_builtin_run(char **argv, int is_piped)
{
	int			i;
	int			ret;
	t_builtin	builtins;

	ft_inicialize_builtins(&builtins);
	ret = 666;
	i = 0;
	if (is_piped)
		i = 4;
	while (i < builtins.num_functions)
	{
		if (ft_strlen(argv[0]) == ft_strlen(builtins.builtin_str[i])
			&& ft_strncmp(argv[0], builtins.builtin_str[i],
				ft_strlen(argv[0])) == 0)
		{
			ret = builtins.builtin_func[i](argv);
			if (!is_piped)
				ft_matrix_free(argv);
			return (ret);
		}
		(i)++;
	}
	return (ret);
}

int	is_valid_env_var_name(char **name_value)
{
	int	i;

	i = 0;
	if (ft_isdigit(name_value[0][0]))
	{
		printf("minishell: export \"%s\": not a valid identifier\n",
			name_value[0]);
		ft_matrix_free(name_value);
		return (0);
	}
	else
	{
		while (name_value[0][i] != '\0')
		{
			if (!(ft_isalnum(name_value[0][i++])))
			{
				printf("minishell: export \"%s\": not a valid identifier\n",
					name_value[0]);
				ft_matrix_free(name_value);
				return (0);
			}
		}
	}
	return (1);
}
