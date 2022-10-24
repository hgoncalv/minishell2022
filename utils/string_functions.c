/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:40:01 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/20 00:58:44 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_remove_chars(char *str, char *chars2remove, int free_original)
{
	t_vars	vars;

	ft_inicialize_vars(&vars);
	vars.tmp_str = ft_realloc(vars.str, (ft_strlen(str) + 1) * sizeof(char));
	while (str[vars.i])
	{
		if (ft_strchr(chars2remove, str[vars.i]))
		{
			vars.i++;
			continue ;
		}
		else
			vars.tmp_str[vars.j] = str[vars.i];
		vars.i++;
		vars.j++;
	}
	vars.tmp_str[vars.j] = '\0';
	vars.str = ft_strdup(vars.tmp_str);
	free(vars.tmp_str);
	if (free_original)
		free(str);
	return (vars.str);
}
