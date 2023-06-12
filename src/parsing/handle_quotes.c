/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:44:40 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/12 18:09:14 by alaparic         ###   ########.fr       */
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

char	*parse_quotes(char *input)
{
	char	c;
	int		n;
	int		j;
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
			n++;
		}
		if (input[n] != c)
			parsed[j++] = input[n];
		if (input[n] == c)
			c = 1;
		n++;
	}
	return (parsed);
}

enum e_quotes	check_flag(char *str, int n, enum e_quotes flag)
{
	int	doub;
	int	findoub;
	int	sing;
	int	finsing;

	findoub = 0;
	finsing = 0;
	sing = 0;
	doub = 0;
	if (*(str + n) == 34)
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
	else if ((flag == SINGLES && *(str + n - 1) == 39 && n - 1 != sing)
		|| (flag == DOUBLE && *(str + n - 1) == 34 && n - 1 != doub))
	{
		if (str[n] == 34)
			findoub = n;
		else if (str[n] == 39)
			finsing = n;
		flag = NONE;
	}
	return (flag);
}
