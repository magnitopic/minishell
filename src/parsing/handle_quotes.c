/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:44:40 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/04 15:40:55 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_unclosed_quotes(char *input)
{
	enum e_quotes	flag;

	flag = NONE;
	while (*input)
	{
		if (*input == 34 && flag == NONE)
			flag = DOUBLE;
		else if (*input == 39 && flag == NONE)
			flag = SINGLE;
		else if ((flag == SINGLE && *input == 39)
			|| (flag == DOUBLE && *input == 34))
			flag = NONE;
		input++;
	}
	if (flag != NONE)
		return (1);
	return (0);
}

static char	*count_quotes(char c, int n, int j, char *input)
{
	while (input[n])
	{
		if ((input[n] == '\'' || input[n] == '"') && c == 1)
		{
			c = input[n];
			n++;
		}
		if (input[n] != c)
			j++;
		if (input[n] == c)
			c = 1;
		n++;
	}
	return (ft_calloc(sizeof(char), (j + 1)));
}

char	*split_quotes(char *input, char **env)
{
	char	c;
	t_vars	v;
	char	*parsed;

	c = 1;
	v.n = 0;
	v.st = 0;
	parsed = count_quotes(c, v.n, v.st, input);
	while (input[v.n])
	{
		if ((input[v.n] == '\'' || input[v.n] == '"') && c == 1)
			c = input[v.n];
		if (input[v.n] != c)
			parsed[v.st++] = input[v.n];
		v.n++;
		if (input[v.n] == c)
		{
			if (c == '"')
				parsed = add_values(parsed, env);
			break ;
		}
	}
	if (ft_strchr(parsed, '$') != NULL && c != '\'')
		parsed = add_values(parsed, env);
	return (parsed);
}

enum e_quotes	check_flag(char *str, int pos)
{
	enum e_quotes	flag;
	int				i;

	flag = NONE;
	i = 0;
	while (i <= pos)
	{
		if (str[i] == '"' && flag == NONE)
			flag = DOUBLE;
		else if (str[i] == '\'' && flag == NONE)
			flag = SINGLE;
		else if ((flag == SINGLE && str[i] == '\'')
			|| (flag == DOUBLE && str[i] == '"'))
			flag = NONE;
		i++;
	}
	return (flag);
}
