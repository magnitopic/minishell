/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:21:13 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/08 11:50:08 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	get_commands(char *input, t_list **com)
{
	enum e_quotes	flag;
	char			*str;
	char			*temp;

	str = input;
	while (*input)
	{
		flag = check_flag(input, 0, flag);
		if (flag == NONE && (*input == 124
				|| *input == 62 || *input == 60))
		{
			temp = ft_substr(str, 0, ft_strlen(str) - ft_strlen(input));
			if (*com == NULL)
				*com = ft_lstnew(temp);
			else
				ft_lstadd_back(com, ft_lstnew(temp));
			str = input;
			if (flag == NONE && (*input == 124
					|| *input == 62 || *input == 60))
				input++;
		}
		input++;
	}
	ft_lstadd_back(com, ft_lstnew(str));
}

void	parsing(char *input, char **paths, char **env)
{
	t_list	*commands;
	char	**test;

	((void)paths, (void)env);
	commands = NULL;
	if (check_quotes(input) == -1)
	{
		perror("unclosed quotes");
		return ;
	}
	get_commands(input, &commands);
	while (commands)
	{
		printf("command: %s\n", commands->content);
		char **arr = parse_words(commands->content, (char **)commands->content);
		int i = 0;
		while (arr[i]){
			printf("|%s|\n", arr[i]);
			expand_var(arr[i], env);
			i++;
		}
		commands = commands->next;
	}
	free_stacks(&commands);
	test = ft_split(input, '|');
	int i = 0;
	while (test[i])
		execution(test[i++], paths, env);
	free_matrix(test);
}
