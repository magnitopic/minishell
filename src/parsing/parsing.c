/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:21:13 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/08 17:01:07 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * This function separates the different commands on to a list
*/
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

static char	*add_values(char *command, char *var_name)
{
	
}

static char	*expand_values(char **command, char **env)
{
	t_list	*variables;
	t_list	*aux;
	static int index = 0;

	while (*command)
	{
		variables = find_name_vars(*command);
		aux = variables;
		while (**command)
		{
			// guardar variables con boolean de simples
			// quitar comillas
			// desarrollar variables
			if (index == 0)
				
			if (ft_strncmp(ft_strchr(**command, '$') + 1, variables, \
				ft_strlen(variables->content)) && check_flag != SINGLES)
				*command = add_values(*command, variables->content);
			*command++;
			variables = variables->next;
		}
		free(aux);
		command++;
	}
}

void	parsing(char *input, char **paths, char **env)
{
	t_list	*commands;
	t_list	*aux;

	((void)paths, (void)env);
	commands = NULL;
	if (check_quotes(input) == -1)
	{
		ft_putstr_fd("\033[0;31mError: Unclosed quotes\033[0;\n", 2);
		return ;
	}
	get_commands(input, &commands);
	aux = commands;
	while (aux)
	{
		aux->content = parse_words(aux->content, env);
		expand_values(aux->content, env);
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
