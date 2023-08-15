/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:08:19 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/15 16:09:05 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_var_value(char *name)
{
	char	*line;
	char	*temp;
	char	**env;
	int		y;

	y = 0;
	env = g_shell->env;
	temp = ft_strjoin(name, "=");
	while (env[y] != NULL && ft_strncmp(temp, env[y], ft_strlen(temp)) != 0)
		y++;
	free(temp);
	if (!env[y] || ft_strlen(env[y]) - ft_strlen(name) == 1)
		return ("");
	line = ft_calloc(ft_strlen(env[y]) - ft_strlen(name), sizeof(char));
	if (!line)
		ft_perror("malloc");
	ft_strlcpy(line, env[y] + ft_strlen(name) + 1, \
		ft_strlen(env[y]) - ft_strlen(name));
	return (line);
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
