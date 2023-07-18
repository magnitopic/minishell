/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:40:45 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/18 12:11:15 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_list	*find_name_vars(char *var)
{
	t_vars	i;
	int		n;
	t_list	*vars;

	n = 0;
	i.len = 0;
	vars = NULL;
	while (var[n])
	{
		if (var[n] == '$')
		{
			i.st = n + 1;
			while (var[++n + 1] && ft_isalpha(var[n + 1]))
				i.len++;
			ft_lstadd_new(&vars, ft_substr(var, i.st, ++i.len));
			i.len = 0;
		}
		n++;
	}
	return (vars);
}

char	*get_var_value(char *name, char **env)
{
	char	*line;
	char	*temp;
	int		y;

	y = 0;
	temp = ft_strjoin(name, "=");
	while (env[y] != NULL && ft_strncmp(temp, env[y], ft_strlen(temp)) != 0)
		y++;
	free(temp);
	if (!env[y])
		return ("");
	line = ft_calloc(ft_strlen(env[y]) - ft_strlen(name), sizeof(char));
	if (!line)
		ft_perror("malloc");
	ft_strlcpy(line, env[y] + ft_strlen(name) + 1, \
		ft_strlen(env[y]) - ft_strlen(name));
	return (line);
}

static int	find_dollar_pos(char *str, int pos)
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

static char	*get_string(char *command, char **env, t_vars v, t_list *vars)
{
	int	i;

	i = 0;
	while (vars)
	{
		v.path = get_var_value(vars->content, env);
		i = find_dollar_pos(command, i);
		v.temp = ft_substr(command, 0, i);
		if (ft_strlen(v.path) < 1)
		{
			v.other_aux = ft_substr(command, i + 1 + ft_strlen(vars->content), \
				ft_strlen(command) - ft_strlen(vars->content) \
				+ ft_strlen(v.path));
			v.temp = ft_strjoin(v.temp, v.other_aux);
			return (v.temp);
		}
		else
		{
			v.other_aux = ft_strjoin(v.temp, v.path);
			free(v.temp);
			v.temp = ft_substr(command, i + 1 + ft_strlen(vars->content),
					ft_strlen(command) - ft_strlen(vars->content)
					+ ft_strlen(v.path));
			v.str = ft_strjoin(v.other_aux, v.temp);
			free(command);
			free(v.other_aux);
			command = v.str;
			i += ft_strlen(vars->content);
			free(v.temp);
		}
		vars = vars->next;
		free(v.path);
	}
	return (v.str);
}

char	*add_values(char *command, char **env)
{
	t_vars	v;
	t_list	*vars;

	v.path = NULL;
	vars = find_name_vars(command);
	if (!vars)
	{
		v.str = ft_substr(command, 0, ft_strlen(command));
		free(command);
		return (v.str);
	}
	v.str = get_string(command, env, v, vars);
	return (v.str);
}
