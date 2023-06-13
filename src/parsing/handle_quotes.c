/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:44:40 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/13 18:33:21 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_quotes(char *input)
{
	enum e_quotes	flag;

	flag = NONE;
	while (*input)
	{
		if (*input == 34 && flag == NONE)
			flag = DOUBLE;
		else if (*input == 39 && flag == NONE)
			flag = SINGLES;
		else if ((flag == SINGLES && *input == 39)
			|| (flag == DOUBLE && *input == 34))
			flag = NONE;
		input++;
	}
	if (flag != NONE)
		return (-1);
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
	int		n;
	int		j;
	int		aux;
	char	*parsed;

	c = 1;
	n = 0;
	j = 0;
	parsed = count_quotes(c, n, j, input);
	while (input[n])
	{
		if ((input[n] == '\'' || input[n] == '"') && c == 1)
		{
			c = input[n];
			aux = n++;
		}
		if (input[n] != c)
			parsed[j++] = input[n];
		n++;
		if (input[n] == c)
		{
			if (c == '"')
			{
				printf("before: %s\n", parsed);
				parsed = add_values(parsed, env);
				printf("after: %s\n", parsed);
			}
			break ;
		}
	}
	if (ft_strchr(parsed, '$') != NULL && c != '\'')
		parsed = add_values(parsed, env);
	return (parsed);
}

enum e_quotes	check_flag(char *str, int n, enum e_quotes flag)
{
	static int	doub = 0;
	static int	findoub = 0;
	static int	sing = 0;
	static int	finsing = 0;

	if ((flag == SINGLES && *(str + n - 1) == 39 && n - 1 != sing)
		|| (flag == DOUBLE && *(str + n - 1) == 34 && n - 1 != doub))
	{
		if (str[n] == 34)
			findoub = n;
		else if (str[n] == 39)
			finsing = n;
		flag = NONE;
	}
	else if (*(str + n) == 34)
	{
		doub = n;
		if (flag == NONE || (flag == SINGLES && finsing == n - 1))
			flag = DOUBLE;
	}
	else if (*(str + n) == 39)
	{
		sing = n;
		if (flag == NONE || (flag == DOUBLE && findoub == n - 1))
			flag = SINGLES;
	}
	return (flag);
}
