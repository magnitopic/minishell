/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:24:48 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/26 13:49:23 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**cpy_env(char **env)
{
	int		len;
	int		i;
	char	**new_env;

	i = -1;
	len = ft_get_matrix_size(env);
	new_env = ft_calloc(len + 1, sizeof(char *));
	if (!new_env)
		ft_perror("malloc");
	while (++i < len)
		new_env[i] = ft_strdup(env[i]);
	return (new_env);
}
