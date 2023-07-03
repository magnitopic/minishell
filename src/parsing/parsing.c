/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:21:13 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/03 11:53:36 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * This function separates the raw user input onto a list where each element is
 * a command
*/
static int	split_commands(char *input, t_list **com)
{
	int		i;
	int		old_i;
	char	*str;

	i = 0;
	old_i = 0;
	while (input[i])
	{
		if (check_flag(input, i) == NONE && i > 0 && input[i] == 124)
		{
			str = ft_substr(input, old_i, i - old_i);
			if (!str)
				return (1);
			ft_lstadd_new(com, ft_strtrim(str, "| "));
			old_i = i;
			free(str);
		}
		i++;
	}
	if (!*com)
		ft_lstadd_new(com, input + old_i);
	else
		ft_lstadd_new(com, ft_strtrim(input + old_i + 1, "| "));
	return (0);
}

static t_command	*coso(char **tokens)
{
	t_command	*new_list;
	int			i;

	i = 0;
	new_list = ft_calloc(1, sizeof(t_command));
	while (*tokens)
	{
		if (**tokens == '<' || **tokens == '>')
			ft_lstadd_new(&new_list->redi, *tokens);
		else if (i++ == 0)
			new_list->comm = *tokens;
		else
			ft_lstadd_new(&new_list->args, *tokens);
		tokens++;
	}
	return (new_list);
}

void	parsing(char *input, char **paths, char **env)
{
	t_list	*commands;
	t_list	*aux;

	commands = NULL;
	if (check_unclosed_quotes(input))
		return (ft_putstr_fd("\033[0;31mError: Unclosed quotes\033[0;\n", 2));
	if (split_commands(input, &commands))
		return (ft_putstr_fd("\033[0;31mError: Syntax error '|'\033[0;\n", 2));
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
		aux->content = coso(aux->content);
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
