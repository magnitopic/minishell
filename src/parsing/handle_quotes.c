/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:44:40 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/08 11:50:29 by alaparic         ###   ########.fr       */
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
	char	*parsed;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] != 39 && input[i] != 34)
			j++;
		i++;
	}
	parsed = malloc(sizeof(char) * (j + 1));
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] != 34 && input[i] != 39)
			parsed[j++] = input[i];
		i++;
	}
	parsed[i] = '\0';
	return (parsed);
}
