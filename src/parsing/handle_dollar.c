/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:40:45 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/20 16:02:58 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*find_name_vars(char *var)
{
	int		n;
	int		len;
	int		start;
	t_list	*vars;

	n = 0;
	len = 0;
	vars = NULL;
	while (var[n])
	{
		if (var[n] == '$' && var[n + 1] && var[n + 1] != 39 && var[n + 1] != 34)
		{
			start = n + 1;
			while (var[++n + 1] && var[n + 1] != ' ' && var[n + 1] != 34
				&& var[n + 1] != 39 && var[n + 1] != '$')
				len++;
			if (!vars)
				vars = ft_lstnew(ft_substr(var, start, len + 1));
			else
				ft_lstadd_back(&vars, ft_lstnew(ft_substr(var, start, ++len)));
			len = 0;
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
	{
		perror("malloc");
		exit (EXIT_FAILURE);
	}
	ft_strlcpy(line, env[y] + ft_strlen(name) + 1, \
		ft_strlen(env[y]) - ft_strlen(name));
	return (line);
}

/* char	*expand_vars(char *str, char **env)
{
	t_list	*commands;
	t_list	*aux;
	char	*path;

	commands = find_name_vars(str);
	aux = commands;
	while (aux)
	{
		path = get_var_value(aux->content, env);
		printf("%s\n", path);
		aux = aux->next;
	}
	free_stacks(&commands);

	return (str);
} */
