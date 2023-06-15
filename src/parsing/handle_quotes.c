/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:44:40 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/15 15:06:05 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_unclosed_quotes(char *input)
{
	enum e_quotes	flag;

	flag = NONE;
	while (*input)
	{
		if (*input == 34 && flag == NONE)
			flag = DOUBLE;
		else if (*input == 39 && flag == NONE)
			flag = SINGLE;
		else if ((flag == SINGLE && *input == 39)
			|| (flag == DOUBLE && *input == 34))
			flag = NONE;
		input++;
	}
	if (flag != NONE)
		return (1);
	return (0);
}

static char	*count_quotes(char c, int n, int j, char *input)
{
	while (input[n])
	{
		if ((input[n] == '\'' || input[n] == '"') && c == 1)
		{
			c = input[n];
			n++;
		}
		if (input[n] != c)
			j++;
		if (input[n] == c)
			c = 1;
		n++;
	}
	return (ft_calloc(sizeof(char), (j + 1)));
}

char	*remove_quotes(char *input)
{
	char	c;
	int		n;
	int		j;
	char	*parsed;

	c = 1;
	n = 0;
	j = 0;
	parsed = count_quotes(c, n, j, input);
	while (input[n])
	{
		if ((input[n] == '\'' || input[n] == '"') && c == 1)
		{
			c = input[n];
			n++;
		}
		if (input[n] != c)
			parsed[j++] = input[n];
		if (input[n] == c)
			c = 1;
		n++;
	}
	return (parsed);
}

enum e_quotes	check_flag(char *str, int pos, enum e_quotes flag)
{
	if (*(str + pos) == '"' && flag == NONE)
		flag = DOUBLE;
	else if (*(str + pos) == '\'' && flag == NONE)
		flag = SINGLE;
	else if ((flag == SINGLE && *(str + pos) == '\'')
		|| (flag == DOUBLE && *(str + pos) == '"'))
		flag = NONE;
	return (flag);
}

int	find_dollar_pos(char *str, int pos)
{
	if (!pos)
		pos = 0;
	while (str[pos])
	{
		if (str[pos] == '$')
			return (pos);
		pos++;
	}
	return (pos);
}

char    *add_values(char *command, char **env)
{
	char    *str;
	char    *path;
	char    *temp;
	char    *other_aux;
	int     i;
	t_list  *vars;

	vars = find_name_vars(command);
	i = 0;
	if (!vars)
	{
		str = ft_substr(command, 0, ft_strlen(command));
		free(command);
	}
	while (vars)
	{
		path = get_var_value(vars->content, env);
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
		free(temp);
		vars = vars->next;
	}
	return (str);
}

char	*split_quotes(char *input, char **env)
{
	char	c;
	int		n;
	int		j;
	char	*parsed;

	c = 1;
	n = 0;
	j = 0;
	parsed = count_quotes(c, n, j, input);
	while (input[n])
	{
		if ((input[n] == '\'' || input[n] == '"') && c == 1)
		{
			c = input[n];¡
		}
		if (input[n] != c)
			parsed[j++] = input[n];
		n++;
		if (input[n] == c)
		{
			if (c == '"')
			{
				printf("before: %s\n", parsed);
				parsed = add_values(parsed, env);
				printf("after: %s\n", parsed);
			}
			break ;
		}
	}
	if (ft_strchr(parsed, '$') != NULL && c != '\'')
		parsed = add_values(parsed, env);
	return (parsed);
}
