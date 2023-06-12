/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:44:40 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/12 16:49:24 by alaparic         ###   ########.fr       */
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

char	*parse_quotes(char *input)
{
	char			*parsed;
	int				i;
	int				j;
	enum e_quotes	flag;

	i = 0;
	j = 0;
	flag = NONE;
	while (input[i])
	{
		flag = check_flag(input, i, flag);
		printf("%d %d\n", input[i], flag);
		if ((input[i] != '\'' && input[i] != '"') || ((input[i] == 39 && flag != SINGLES) || (input[i] == 34 && flag != DOUBLE)))
			j++;
		i++;
	}
	parsed = ft_calloc(sizeof(char), (j + 1));
	i = 0;
	j = 0;
	flag = NONE;
	while (input[i])
	{
		flag = check_flag(input, i, flag);
		if ((input[i] != 39 && input[i] != 34) || ((input[i] == 39 && flag != SINGLES) || (input[i] == 34 && flag != DOUBLE)))
			parsed[j++] = input[i];
		i++;
	}
	return (parsed);
}

enum e_quotes	check_flag(char *str, int n, enum e_quotes flag)
{
	static int	doub = 0;
	static int	sing = 0;

	if (*(str + n) == 34)
	{
		doub = n;
		if (flag == NONE || (flag == SINGLES && sing ==  n - 1))
			flag = DOUBLE;
	}
	else if (*(str + n) == 39)
	{
		sing = n;
		if (flag == NONE || (flag == DOUBLE && doub == n - 1))
			flag = SINGLES;
	}
	else if ((flag == SINGLES && *(str + n - 1) == 39 && n - 1 != sing)
		|| (flag == DOUBLE && *(str + n - 1) == 34 && n - 1 != doub))
		flag = NONE;
	return (flag);
}
