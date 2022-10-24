/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:20:56 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/21 10:04:43 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr_byarrayofchars(char *str, char *sepa)
{
	if (!str)
		return (NULL);
	while (*str && !ft_strchr(sepa, *str))
		str++;
	if (str && *str == '\0')
		return (NULL);
	return (str);
}

char	**ft_get_jump_interval(char **str, char *chars2jump)
{
	char	**interval;

	interval = NULL;
	interval = ft_realloc(interval, 2 * sizeof(char *));
	if (!*str)
		return (NULL);
	interval[1] = NULL;
	interval[0] = ft_strchr_byarrayofchars(*str, chars2jump);
	if (interval[0] == NULL)
	{
		free(interval);
		return (NULL);
	}
	if (*interval[0] == 2)
		interval[1] = ft_strchr(interval[0] + 1, 3);
	else if (*interval[0] == '(')
		interval[1] = ft_strchr(interval[0] + 1, ')');
	else
		interval[1] = ft_strchr(interval[0] + 1, *interval[0]);
	if (interval[1] == NULL)
	{
		free(interval);
		return (NULL);
	}
	return (interval);
}

char	*ft_strtok_quote_aware_start(char *str, char **lasts, const char *sep)
{
	if (!str)
		str = *lasts;
	while (*str && ft_strchr(sep, *str))
		++str;
	return (str);
}

char	*ft_strtok_quote_aware(char *str, const char *sep, char *chars2jump)
{
	static char	*lasts;
	char		*token;
	char		**quotes;

	str = ft_strtok_quote_aware_start(str, &lasts, sep);
	if (*str == '\0')
		return (NULL);
	token = str;
	while (*str && !ft_strchr(sep, *str))
	{
		quotes = ft_get_jump_interval(&str, chars2jump);
		if (quotes)
		{
			if (str == quotes[0])
				str = quotes[1];
		}
		++str;
		free(quotes);
	}
	if (*str)
		*str++ = '\0';
	lasts = str;
	return (token);
}
