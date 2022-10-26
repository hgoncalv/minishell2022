#include "../minishell.h"

int r_size(char *s)
{
	int is_special;
	int size;

	size = 0;
	is_special = -1;
	while (s && *s)
	{
		if (is_whitespace(*s))
		{
			if (is_special != 0)
				is_special = 0;
		}
		else if (is_special_parse(*s))
		{
			is_special = 1;
			size++;
		}
		else
		{
			if (is_special != 2)
			{
				is_special = 2;
				size++;
			}
		}
		s++;
	}
	return (size);
}

int ft_strcount_char(char *str, char l)
{
	int i;

	i = 0;
	if (!str || !l)
		return (0);
	while (*str)
	{
		if (*str == l)
			i++;
		str++;
	}
	return (i);
}

int is_whitespace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

int is_special_parse(int c)
{
	return (c == '<' || c == '>' || c == '|');
}

void ft_stradd(char **str, char *add)
{
	int i;

	if (*str == NULL)
		return;
	i = 0;
	while ((*str)[i])
		i++;
	(*str) = realloc((*str), ft_strlen(*str) + ft_strlen(add) + 1);
	while (*add)
	{
		(*str)[i++] = *add;
		add++;
	}
	(*str)[i] = 0;
}
