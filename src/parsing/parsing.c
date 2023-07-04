/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:21:13 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/04 20:09:33 by alaparic         ###   ########.fr       */
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
		if (check_flag(input, i) == NONE && input[i] == 124)
		{
			str = ft_substr(input, old_i, i - old_i);
			if ((ft_strlen(ft_strtrim(str, "| ")) < 1)
				|| (input[i] == '|' && !input[i + 1]))
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

/**
 * The command elements are split into the actual command, it's arguments and
 * the redirects to and from files
*/
static t_command	*structure(t_list *tokens)
{
	t_command	*new_list;
	int			i;
	char		*str;

	i = 0;
	new_list = ft_calloc(1, sizeof(t_command));
	while (tokens)
	{
		str = tokens->content;
		if ((*str == '<' || *str == '>'))
		{
			ft_lstadd_new(&new_list->redi, str);
		}
		else if (i++ == 0)
			new_list->comm = str;
		else
			ft_lstadd_new(&new_list->args, str);
		tokens = tokens->next;
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
		t_list	*auxaux = aux->content;
		printf("\033[0;35mParsed:\033[0m\n");
		while (auxaux)
		{
			printf("%s\n", (char *)auxaux->content);
			auxaux = auxaux->next;
		}
		printf("\033[0;35m--------------------\033[0m\n");
		aux->content = structure(aux->content);
		aux = aux->next;
	}
	aux = commands;
	while (commands)
	{
		execution(commands->content, paths, env);
		commands = commands->next;
	}
	free_commands(aux);
}
