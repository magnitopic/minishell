/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:21:13 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/26 17:20:15 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * This function separates the raw user input onto a list where each element is
 * a command
*/
int	split_commands(char *input, t_list **com)
{
	int	i;
	int	old_pos;

	i = 0;
	old_pos = 0;
	while (input[i])
	{
		if (check_flag(input, i) == NONE && i > 0 && input[i] == 124)
		{
			char *test = ft_strtrim(ft_substr(input, old_pos, i - old_pos), "|");
			if (*test == '\0')
				return (1);
			ft_lstadd_new(com, test);
			old_pos = i;
			printf("\"%s\"\n", test);
		}
		i++;
	}
	ft_lstadd_new(com, input + old_pos);
	return (0);
}

void	parsing(char *input, char **paths, char **env)
{
	t_list	*commands;
	t_list	*aux;

	commands = NULL;
	if (check_unclosed_quotes(input))
	{
		ft_putstr_fd("\033[0;31mError: Unclosed quotes\033[0;\n", 2);
		return ;
	}
	if (split_commands(input, &commands))
	{
		ft_putstr_fd("\033[0;31mError: \033[0;\n", 2);
		return ;
	}
	aux = commands;
	while (aux)
	{
		aux->content = split_words(aux->content);
		aux->content = expand_values(aux->content, env);
		int i = 0;
		printf("\033[0;35mParsed:\033[0m\n");
		while (((char **)aux->content)[i])
			printf("%s\n", ((char **)aux->content)[i++]);
		printf("\033[0;35m--------------------\033[0m\n");
		aux = aux->next;
	}
	aux = commands;
	while (commands)
	{
		execution(commands->content, paths, env);
		commands = commands->next;
	}
	free_stacks(&aux);
}
