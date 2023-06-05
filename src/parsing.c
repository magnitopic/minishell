/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:21:13 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/05 16:32:32 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*static int	check_quotes(char *input)
{
	if (ft_strchr(input, 39) == NULL || ft_strchr(input, 34) == NULL)
		return (0);
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
			str = NULL;
			j++;
		}
		input++;
	}
}*/

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
	//int		flag;

	//flag = check_quotes(input);
	quotes(input);
	commands = ft_split(input, '|');
	while (*commands)
		execution(*commands++, paths, env);
}
