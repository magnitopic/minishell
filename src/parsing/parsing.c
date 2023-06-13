/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:21:13 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/13 14:18:39 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * This function separates the different commands onto a list
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

static char	*add_values(char *command, char *var_name, int i, char **env)
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
	free(path);
	free(command);
	free(temp);
	return (str);
}

t_vars	find_pos(char *str, t_vars pos)
{
	int		j;
	int		i;
	char	c;

	j = 0;
	i = 0;
	c = 1;
	while (command[j][i])
		{
			if ((command[j][i] == '\'' || command[j][i] == '"') && c == 1)
			{
				c = command[j][i];
				pos.in = i++;
				while ((command[j][i] != c)
					i++;
				
				c = 1;
			}
			else if (command[j][i] == '$')
		}
}
// recibe un char ** con los 
static char	**expand_values(char **command, char **env)
{
	int				j;
	int				i;
	char			c;
	char			*temp;
	t_vars			pos;
	enum e_quotes	flag;

	flag = NONE;
	i = 0;
	j = 0;
	c = 1;
	while (command[j])
	{
		while (pos.end != ft_strlen(command[j]) - 1)
		{
			pos = find_pos()
		}
		//free(aux);
		j++;
		i = 0;
	}
	return (command);
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
		aux->content = split_words(aux->content);
		aux->content = expand_values(aux->content, env);
		int i = 0;
		while (((char **)aux->content)[i])
			printf("no-quotes: %s\n", ((char **)aux->content)[i++]);
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
