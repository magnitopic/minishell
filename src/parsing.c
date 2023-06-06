/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:21:13 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/06 14:53:39 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_quotes(char *input)
{
	enum e_quotes	flag;

	flag = NONE;
	while (*input)
	{
		if (*input == 34 && flag == NONE)
		{
			flag = DOUBLE;
			input++;
		}
		else if (*input == 39 && flag == NONE)
		{
			flag = SINGLES;
			input++;
		}
		if ((flag == SINGLES && *input == 39)
			|| (flag == DOUBLE && *input == 34))
			flag = NONE;
		input++;
	}
	if (flag != NONE)
		return (-1);
	return (0);
}

/* static void	quotes(char *input)
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
			printf("%s\n", ft_substr(str, 0, ft_strlen(str) - ft_strlen(input)));
			str = NULL;
		}
		input++;
	}
} */

static void	get_commands(char *input, t_list **com)
{
	enum e_quotes	flag;
	char			*str;
	char			*temp;

	str = input;
	while (*input)
	{
		if (*input == 34 && flag == NONE)
			flag = DOUBLE;
		else if (*input == 39 && flag == NONE)
			flag = SINGLES;
		else if ((flag == SINGLES && *input == 39)
			|| (flag == DOUBLE && *input == 34))
			flag = NONE;
		if (flag == NONE && *input == 124)
		{
			temp = ft_substr(str, 0, ft_strlen(str) - ft_strlen(input));
			if (*com == NULL)
				*com = ft_lstnew(temp);
			else
				ft_lstadd_back(com, ft_lstnew(temp));
			str = input;
			printf("str: %s\n", temp);
		}
		input++;
	}
	printf("str: %s\n", str);
	ft_lstadd_back(com, ft_lstnew(str));
}

void	parsing(char *input, char **paths, char **env)
{
	t_list	*commands;
	int		flag;

	((void)paths, (void)env);
	commands = NULL;
	flag = check_quotes(input);
	if (flag == -1)
	{
		perror("unclosed quotes");
		return ;
	}
	get_commands(input, &commands);
	//quotes(input, commands);
	/* while (*input)
	{
		if (*input == 34 || *input == 39)
			quotes(input);
		if (*input == 124 )
		input++;
	} */
	/* commands = ft_split(input, '|');
	while (*commands)
		execution(*commands++, paths, env); */
}
