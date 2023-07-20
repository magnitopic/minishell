/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:21:13 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/20 10:36:33 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * It was at a wine party-
 * I lay in a drowse, knowing it not.
 * The blown flowers fell and filled my lap.
 * When I arose, still drunken,
 * The birds had all gone to their nests,
 * And there remained but few of my comrades.
 * I went along the river—alone in the moonlight.
*/
static t_list	*delete_emptiness(t_list *list)
{
	t_list	*aux;
	t_list	*list_cpy;
	char	*temp;

	aux = list;
	list_cpy = NULL;
	temp = "";
	while (aux != NULL)
	{
		if (temp && ft_strlen(temp) > 0)
			temp = NULL;
		temp = ft_strtrim(aux->content, " 	");
		if (ft_strlen(temp) >= 1)
			ft_lstadd_new(&list_cpy, temp);
		else
			(free(temp), temp = NULL);
		aux = aux->next;
	}
	free_stacks(&list);
	return (list_cpy);
}

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
	// TODO: add flag to check if there is a command and send appropriate error message
	t_command		*new_list;
	int				i;
	char			*str;
	char			*trim_aux;

	i = 0;
	new_list = ft_calloc(1, sizeof(t_command));
	while (tokens)
	{
		str = tokens->content;
		trim_aux = ft_strtrim(str, "<>");
		if (ft_strlen(trim_aux) == 0)
		{
			if (handle_redirects(str, &(new_list->redi), &tokens))
				return (NULL);
		}
		else if (i++ == 0)
			new_list->comm = str;
		else
			ft_lstadd_new(&new_list->args, str);
		tokens = tokens->next;
		free(trim_aux);
	}
	return (new_list);
}

/**
 * Main parsing function which will call all other functions needed for parsing
*/
void	parsing(char *input, char **paths, char **env)
{
	t_list	*commands;
	t_list	*aux;
	t_files	*files;

	files = ft_calloc(1, sizeof(t_files));
	files->fd = ft_calloc(3, sizeof(int));
	commands = NULL;
	if (check_unclosed_quotes(input))
		return (ft_putstr_fd("\033[0;31mError: Unclosed quotes\033[0;\n", 2));
	if (split_commands(input, &commands))
		return (ft_putstr_fd("\033[0;31mError: Syntax error '|'\033[0;\n", 2));
	aux = commands;
	while (aux)
	{
		aux->content = split_words(aux->content);
		aux->content = delete_emptiness(aux->content);
		aux->content = expand_values(aux->content, env);
		aux->content = structure(aux->content);
		if (aux->content == NULL)
			return (ft_putstr_fd("\033[0;31mError: Bad redirect\033[0;\n", 2));
		aux = aux->next;
	}
	exec(commands, files, paths, env);
}
