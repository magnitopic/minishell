/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:21:13 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/09 16:38:38 by alaparic         ###   ########.fr       */
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
 * 
 * FUNCIÓN IMPORTANTE NO BORRAR
*/
static t_list	*delete_emptiness(t_list *list)
{
	t_list	*aux;
	t_list	*list_cpy;
	char	*temp;

	aux = list;
	list_cpy = NULL;
	temp = "";
	while (list != NULL)
	{
		if (temp && ft_strlen(temp) > 0)
			temp = NULL;
		temp = ft_strtrim(list->content, " 	");
		if (ft_strlen(temp) >= 1)
			ft_lstadd_new(&list_cpy, temp);
		else
			(free(temp), temp = NULL);
		list = list->next;
	}
	free_lists(&aux);
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
	char	*str_trim;

	i = 0;
	old_i = 0;
	while (input[i])
	{
		if (check_flag(input, i) == NONE && input[i] == 124)
		{
			str = ft_substr(input, old_i, i - old_i);
			str_trim = ft_strtrim(str, "| ");
			if ((ft_strlen(str_trim) < 1) || (input[i] == '|' && !input[i + 1]))
				return (free(str), free(str_trim), 1);
			(ft_lstadd_new(com, str_trim), free(str));
			old_i = i;
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
static t_command	*structure(t_tokens *tokens)
{
	t_command	*new_list;
	int			i;
	char		*str;
	t_tokens	*aux;

	i = 0;
	new_list = ft_calloc(1, sizeof(t_command));
	aux = tokens;
	while (tokens)
	{
		str = tokens->content;
		//printf("Str: %s\n", str);
		if ((ft_strchr(str, '<') || ft_strchr(str, '>'))
			&& tokens->flag == 0)
			handle_redirects(str, &(new_list->redi), &tokens);
		else if (i++ == 0)
			new_list->comm = str;
		else
			ft_lstadd_new(&new_list->args, str);
		tokens = tokens->next;
	}
	free_tokens(&aux);
	return (new_list);
}

static int	error_handling(char *input, t_files *files, t_list **commands)
{
	if (check_unclosed_quotes(input))
	{
		g_shell->exit_stat = 1;
		free_files(files);
		ft_putstr_fd("\033[0;31mError: Unclosed quotes\033[0;\n", 2);
		return (1);
	}
	if (split_commands(input, commands))
	{
		g_shell->exit_stat = 258;
		free_lists(commands);
		free_files(files);
		ft_putstr_fd("\033[0;31mError: Syntax error '|'\033[0;\n", 2);
		return (1);
	}
	if (!check_invalid_redirects(input))
	{
		g_shell->exit_stat = 258;
		free_files(files);
		ft_putstr_fd("\033[0;31mBad redirect\033[0m\n", 2);
		return (1);
	}
	return (0);
}

/**
 * Main parsing function which will call all other functions needed for parsing.
 * Once finished, the parsed input will be passed on to the `exec` function.
*/
void	parsing(char *input)
{
	t_list	*commands;
	t_list	*aux;
	t_files	*files;

	files = ft_calloc(1, sizeof(t_files));
	commands = NULL;
	if (error_handling(input, files, &commands))
		return ;
	aux = commands;
	while (aux)
	{
		aux->content = split_words(aux->content);
		aux->content = delete_emptiness(aux->content);
		aux->content = expand_values(aux->content);
		aux->content = structure(aux->content);
		aux = aux->next;
	}
	if (check_redis(commands))
		exec(commands, files);
	else
		(free_commands(commands), free_files(files));
}
