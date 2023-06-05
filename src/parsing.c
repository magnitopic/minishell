/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:21:13 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/05 18:13:02 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_quotes(char *input)
{
	enum e_quotes	flag;
	char			*str;

	flag = NONE;
	while (*input)
	{
		if (*input == 34 && flag == NONE)
		{
			flag = DOUBLE;
			str = ++input;
		}
		else if (*input == 39 && flag == NONE)
		{
			flag = SINGLES;
			str = ++input;
		}
		if ((flag == SINGLES && *input == 39)
			|| (flag == DOUBLE && *input == 34))
		{
			flag = NONE;
			str = NULL;
		}
		input++;
	}
	if (flag == NONE)
		return (1);
	return (-1);
}

static void	quotes(char *input)
{
	//char			**tokens;
	enum e_quotes	flag;
	int				j;
	char			*str;

	j = 0;
	flag = NONE;
	//tokens = no sabemos, habría que ver cómo lo gestionamos;
	while (*input)
	{
		if (*input == 34 && flag == NONE)
		{
			flag = DOUBLE;
			str = ++input;
		}
		else if (*input == 39 && flag == NONE)
		{
			flag = SINGLES;
			str = ++input;
		}
		if ((flag == SINGLES && *input == 39) || (flag == DOUBLE && *input == 34))
		{
			flag = NONE;
			//tokens[j] = ft_substr(str, 1, ft_strlen(str) - ft_strlen(input));
			printf("cosas: %s\n", ft_substr(str, 0, ft_strlen(str) - ft_strlen(input)));
			str = NULL;
			j++;
		}
		input++;
	}
	/* if (flag != NONE)
		return (-1); */
}

void	parsing(char *input, char **paths, char **env)
{
	char	**commands;
	int		flag;
	int		n;

	flag = check_quotes(input);
	if (flag == -1)
	{
		perror("unclosed quotes");
		return ;
	}
	n = 0;
	/*while (input[n])
	{
		if (input[n] == 34 || input[n] == 39)
			quotes(input);
	}*/
	quotes(input);
	commands = ft_split(input, '|');
	while (*commands)
		execution(*commands++, paths, env);
}
