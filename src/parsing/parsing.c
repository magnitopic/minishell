/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:21:13 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/21 14:47:01 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * This function separates the raw user input onto a list where each element is
 * a command
*/
t_list	*split_commands(char *input, t_list *com)
{
	char			*str;
	char			*temp;
	int				i;
	int				old_pos;

	str = input;
	i = 0;
	old_pos = 0;
	while (input[i])
	{
		if (check_flag(input, i) == NONE && (input[i] == 124
				|| (input[i] == 62 && input[i - 1] != 62) || (input[i] == 60 && input[i - 1] != 60)))
		{
			temp = ft_substr(str, old_pos, i - old_pos);
			if (com == NULL)
				com = ft_lstnew(temp);
			else
				ft_lstadd_back(&com, ft_lstnew(temp));
			str = input;
			old_pos = i;
		}
		i++;
	}
	ft_lstadd_back(&com, ft_lstnew(str + old_pos));
	return (com);
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
	commands = split_commands(input, commands);
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
