/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:44:40 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/03 16:56:19 by jsarabia         ###   ########.fr       */
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

char	*split_quotes(char *input)
{
	char	c;
	t_vars	v;

	c = 1;
	v.n = 0;
	v.st = 0;
	v.parsed = count_quotes(c, v.n, v.st, input);
	while (input[v.n])
	{
		if ((input[v.n] == '\'' || input[v.n] == '"') && c == 1)
			c = input[v.n];
		if (input[v.n] != c)
			v.parsed[v.st++] = input[v.n]; // TODO Fix leak
		v.n++;
		if (input[v.n] == c)
		{
			if (c == '"')
				v.parsed = add_values(v.parsed);
			break ;
		}
	}
	while (ft_strchr(v.parsed, '$') != NULL
		&& (ft_isalpha(v.parsed[find_dollar_pos(v.parsed, 0) + 1])
			|| v.parsed[find_dollar_pos(v.parsed, 0) + 1] == '?')
		&& c != '\'')
		v.parsed = add_values(v.parsed);
	return (v.parsed);
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
