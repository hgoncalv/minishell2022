/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:21:01 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/23 17:28:15 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_words(char *line)
{
	int			words;
	t_values	v;

	words = 0;
	v = ft_init_values(v);
	while (line[v.i])
	{
		v.quote = ft_is_quote(line[v.i], v.quote);
		if (v.quote != 0)
		{
			v = ft_helper_count(v, line);
			words++;
			v.i++;
		}
		else if (v.quote == 0)
		{
			v = ft_helper_quote(v, line);
			words++;
			v.i++;
		}
	}
	return (words);
}

t_values	ft_get_the_value_for_sub(char *line, t_values value)
{
	if (value.quote == 0)
	{
		while (line[value.i] && (line[value.i] == '\"'
				|| line[value.i] == '\''))
			value.i++;
		value = ft_if_quote_z(line, value);
	}
	else
	{
		if (value.i == 0 || (value.quote == 2 && line[value.i] == '\"')
			|| (value.quote == 1 && line[value.i] == '\''))
			value.start = value.i + 1;
		else
			value.start = value.i;
		while (line[value.i] && value.quote != 0)
		{
			if (value.i >= (int)ft_strlen(line))
				break ;
			value.i++;
			value.quote = ft_is_quote(line[value.i], value.quote);
		}
	}
	return (value);
}

char	**ft_get_arr(char **arr, t_values value, char *line)
{
	while (value.i <= (int)ft_strlen(line) && line[value.i])
	{
		if (line[value.i] == 2)
		{
			value.start = ++value.i;
			while (line[value.i] && line[value.i] != 3)
				value.i++;
			arr[value.j] = ft_substr(line, value.start, value.i - value.start);
			value.i += 1;
			value.j++;
			continue ;
		}
		value.quote = ft_is_quote(line[value.i], value.quote);
		value = ft_get_the_value_for_sub(line, value);
		arr[value.j] = ft_substr(line, value.start, value.i - value.start);
		value.j++;
		if (value.i > (int)ft_strlen(line) || line[value.i] == '\0')
			break ;
		value.i++;
	}
	arr[value.j] = NULL;
	return (arr);
}

char	*ft_update_line(char *line)
{
	t_values	value;
	char		**arr;
	char		*new_line;

	arr = NULL;
	value = ft_init_values(value);
	arr = ft_realloc(arr, (ft_count_words(line) + 2) * sizeof(char *));
	arr = ft_get_arr(arr, value, line);
	new_line = ft_concat_multi(arr, NULL);
	ft_matrix_free(arr);
	return (new_line);
}
