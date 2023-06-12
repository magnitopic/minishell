/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:21:13 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/12 19:09:08 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * This function separates the raw user input onto a list where each element is
 * a command
*/
static void	split_commands(char *input, t_list **com)
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

/* static char	*add_values(char *command, char *var_name, int i, char **env)
{
	char	*str;
	char	*path;
	char	*temp;
	char	*other_aux;
	int		len;

	path = return_variable(var_name, env);
	len = ft_strlen(command) - ft_strlen(var_name) + ft_strlen(path);
	temp = ft_substr(command, 0, i);
	other_aux = ft_strjoin(temp, path);
	free(temp);
	temp = ft_substr(command, i + 1 + ft_strlen(var_name), len);
	str = ft_strjoin(other_aux, temp);
	printf("hola amigo: %s\n", str);
	free(path);
	free(command);
	free(temp);
	return (str);
} */

static void	expand_values(char **command, char **env)
{
	t_list		*variables;
	int				j;
	int				i;
	enum e_quotes	flag;

	flag = NONE;
	i = 0;
	j = 0;
	while (command[j])
	{
		variables = find_name_vars(command[j]);
		while (command[j][i] && variables)
		{
			while (command[j][i] != '$' && command[j][i])
				flag = check_flag(command[j], i++, flag);
			if (ft_strncmp(ft_strchr(command[j], '$') + 1, variables->content, \
				ft_strlen(variables->content)) == 0 && check_flag(command[j], i, flag) != SINGLES)
				command[j] = add_values(command[j], variables->content, i, env);
			printf("no-quotes: %s, flag: %d\n", parse_quotes(command[j]), check_flag(command[j], i, flag));
			variables = variables->next;
		}
		j++;
		i = 0;
	}
}

void	parsing(char *input, char **paths, char **env)
{
	t_list	*commands;
	t_list	*aux;

	commands = NULL;
	if (check_quotes(input) == -1)
	{
		ft_putstr_fd("\033[0;31mError: Unclosed quotes\033[0;\n", 2);
		return ;
	}
	split_commands(input, &commands);
	aux = commands;
	while (aux)
	{
		aux->content = split_words(aux->content);
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
