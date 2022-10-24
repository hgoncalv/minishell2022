/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:35:30 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/10/21 12:44:22 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_values	ft_helper_count(t_values v, char *line)
{
	while (line[v.i] && v.quote != 0)
	{
		v.quote = ft_is_quote(line[v.i], v.quote);
		if (v.i >= (int)ft_strlen(line) || line[v.i + 1] == '\0')
			break ;
		v.i++;
	}
	return (v);
}

t_values	ft_helper_quote(t_values v, char *line)
{
	while (line[v.i] && v.quote == 0)
	{			
		v.quote = ft_is_quote(line[v.i], v.quote);
		if (v.i >= (int)ft_strlen(line) || line[v.i + 1] == '\0')
			break ;
		v.i++;
	}
	return (v);
}

t_values	ft_if_quote_z(char *line, t_values value)
{
	value.start = value.i;
	while (line[value.i] && value.quote == 0)
	{
		if (value.i >= (int)ft_strlen(line))
			break ;
		value.i++;
		value.quote = ft_is_quote(line[value.i], value.quote);
	}
	return (value);
}
