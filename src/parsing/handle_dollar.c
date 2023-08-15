/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:40:45 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/15 16:11:47 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_list	*name_vars(char *var, int n, t_vars i, t_list *vars)
{
	while (var[n])
	{
		if (var[n] == '$' && var[n + 1] && (ft_isalpha(var[n + 1])
				|| var[n + 1] == '?' || var[n + 1] == '_'))
		{
			if (!var[n + 1])
			{
				ft_lstadd_new(&vars, ft_substr(var, n, 1));
				break ;
			}
			i.st = n + 1;
			while (var[++n + 1] && (ft_isalpha(var[n + 1])
					|| var[n + 1] == '?' || var[n + 1] == '_'))
				i.len++;
			ft_lstadd_new(&vars, ft_substr(var, i.st, ++i.len));
			i.len = 0;
		}
		n++;
	}
	return (vars);
}

static t_list	*find_name_vars(char *var)
{
	t_vars	i;
	int		n;
	t_list	*vars;

	n = 0;
	i.len = 0;
	vars = NULL;
	vars = name_vars(var, n, i, vars);
	return (vars);
}

int	check_path_status(t_vars v, char **command, t_list *vars, char **aux)
{
	if (ft_strlen(v.path) < 1)
	{
		v.other_aux = ft_substr(*command, v.i + 1 + ft_strlen(vars->content), \
			ft_strlen(*command) - ft_strlen(vars->content) \
			+ ft_strlen(v.path));
		*aux = ft_strjoin(v.temp, v.other_aux);
		free(v.temp);
		free(*command);
		free(v.other_aux);
		return (1);
	}
	v.other_aux = ft_strjoin(v.temp, v.path);
	free(v.temp);
	v.temp = ft_substr(*command, v.i + 1 + ft_strlen(vars->content),
			ft_strlen(*command) - ft_strlen(vars->content)
			+ ft_strlen(v.path));
	v.str = ft_strjoin(v.other_aux, v.temp);
	free(v.other_aux);
	free(*command);
	*command = v.str;
	v.i += ft_strlen(vars->content);
	free(v.temp);
	return (0);
}

static char	*get_string(char *command, t_vars v, t_list *vars)
{
	char	*aux;

	v.i = 0;
	while (vars)
	{
		if (!ft_strcmp(vars->content, "?"))
		{
			free(command);
			v.path = ft_itoa(g_shell->exit_stat);
			return (v.path);
		}
		v.path = get_var_value(vars->content);
		v.i = find_dollar_pos(command, v.i);
		v.temp = ft_substr(command, 0, v.i);
		if (check_path_status(v, &command, vars, &aux))
			return (aux);
		free(v.path);
		vars = vars->next;
	}
	return (command);
}

char	*add_values(char *command)
{
	t_vars	v;
	t_list	*vars;

	v.path = NULL;
	if (ft_strchr(command, '$') == NULL)
		return (command);
	vars = find_name_vars(command);
	v.str = get_string(command, v, vars);
	free_lists(&vars);
	return (v.str);
}
