/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:21:13 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/13 18:55:58 by jsarabia         ###   ########.fr       */
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

char	*add_values(char *command, char **env)
{
	char	*str;
	char	*path;
	char	*temp;
	char	*other_aux;
	int		i;
	t_list	*vars;

	vars = find_name_vars(command);
	i = 0;
	if (!vars)
	{
		str = ft_substr(command, 0, ft_strlen(command));
		free(command);
	}
	while (vars)
	{
		path = return_variable(vars->content, env);
		i = find_dollar_pos(command, i);
		temp = ft_substr(command, 0, i);
		if (!path)
			return (temp);
		other_aux = ft_strjoin(temp, path);
		free(temp);
		temp = ft_substr(command, i + 1 + ft_strlen(vars->content),
				ft_strlen(command) - ft_strlen(vars->content) + ft_strlen(path));
		str = ft_strjoin(other_aux, temp);
		free(command);
		command = str;
		i += ft_strlen(vars->content);
		free(path);
		free(temp);
		vars = vars->next;
	}
	return (str);
}

t_vars	find_pos(char *str, t_vars pos)
{
	int		i;
	char	c;

	i = pos.end;
	c = 1;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && c == 1 && str[i + 1])
		{
			c = str[i];
			pos.in = i++;
			while (str[i] != c)
				i++;
			pos.end = i;
			return (pos);
		}
		else if (str[i] == '$')
		{
			pos.in = i;
			pos.end = ft_strlen(str) - 1;
			return (pos);
		}
		i++;
	}
	pos.end = ft_strlen(str) - 1;
	return (pos);
}
// recibe un char ** con los

static char	**expand_values(char **command, char **env)
{
	int				j;
	char			c;
	t_vars			pos;
	enum e_quotes	flag;

	flag = NONE;
	j = 0;
	c = 1;
	pos.in = 0;
	pos.end = 0;
	while (command[j])
	{
		while (pos.end != (int)ft_strlen(command[j]) - 1)
		{
			if (pos.in == 0)
			{
				pos = find_pos(command[j], pos);
				pos.str = ft_substr(command[j], 0, pos.end + 1);
			}
			pos = find_pos(command[j], pos);
			pos.temp = ft_substr(command[j], pos.in, pos.end - pos.in + 1);
			pos.temp = split_quotes(pos.temp, env);
			pos.aux = ft_substr(pos.str, 0, ft_strlen(pos.str));
			free(pos.str);
			pos.str = ft_strjoin(pos.aux, pos.temp);
			free(pos.aux);
			free(pos.temp);
		}
		free(command[j]);
		command[j] = ft_substr(pos.str, 0, ft_strlen(pos.str));
		pos.in = 0;
		pos.end = 0;
		j++;
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
		aux->content = parse_words(aux->content);
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
