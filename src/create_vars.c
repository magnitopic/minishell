/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:04:24 by jsarabia          #+#    #+#             */
/*   Updated: 2023/07/18 12:10:04 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*create_vars(char *origin, char **env)
{
	int		n;
	char	*line;

	n = 0;
	while (env[n])
	{
		if (ft_strncmp(origin, env[n], ft_strlen(origin)) == 0)
		{
			line = ft_calloc(ft_strlen(env[n]) - ft_strlen(origin) + 1,
					sizeof(char));
			if (!line)
				ft_perror("malloc");
			ft_strlcpy(line, env[n] + ft_strlen(origin) + 1, ft_strlen(env[n])
				- ft_strlen(origin) + 1);
			return (line);
		}
		n++;
	}
	return (NULL);
}
