/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:32:55 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/28 15:20:51 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_program(char *message)
{
	printf("%s", message);
	exit(EXIT_SUCCESS);
}

void	ft_perror(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	set_prompt(void)
{
	char	*aux;
	char	path[PATH_MAX];

	g_sl->prompt = ft_strjoin(PROMPT1, getcwd(path, sizeof(path)));
	aux = g_sl->prompt;
	g_sl->prompt = ft_strjoin(aux, PROMPT2);
	free(aux);
}

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
