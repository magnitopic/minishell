/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:21:13 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/10 16:55:36 by jsarabia         ###   ########.fr       */
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
 * Auxiliary function to check if the redirect and the next command need to be
 * joined
*/
static int	check_separate_redirect(char *str, t_list *tokens)
{
	int	flag;

	flag = 0;
	while (*str)
	{
		if (*str != '<' || *str != '>')
			flag = 1;
		str++;
	}
	if (tokens->next == NULL)
		flag = 0;
	return (flag);
}

/**
 * The command elements are split into the actual command, it's arguments and
 * the redirects to and from files
*/
static t_command	*structure(t_list *tokens)
{
	t_command		*new_list;
	int				i;
	char			*str;
	enum e_redirect	red;

	i = 0;
	new_list = ft_calloc(1, sizeof(t_command));
	while (tokens)
	{
		str = tokens->content;
		printf("%s\n", str);
		if (*str == '<' || *str == '>')
		{
			red = handle_redirects(str);
			if (red == 4)
				exit(EXIT_FAILURE); // TODO: hacer una función que salga del programa dando error
			if (check_separate_redirect(str, tokens))
			{
				str = ft_strjoin(str, tokens->next->content);
				tokens = tokens->next;
			}
			ft_newcommand(&new_list->redi, str, red);
		}
		else if (i++ == 0)
			new_list->comm = str;
		else
			ft_lstadd_new(&new_list->args, str);
		tokens = tokens->next;
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
		aux = aux->next;
	}
	aux = commands;
	while (commands)
	{
		print_commands(commands->content, paths, env);
		execute_final(commands->content, paths, env);
		/*else
			execute_pipe(commands->content, paths, env);*/
		commands = commands->next;
	}
	free_commands(aux);
}
