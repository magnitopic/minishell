/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:32:55 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/10 18:41:52 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_program(char *message, int err_code)
{
	ft_putstr_fd(message, 2);
	exit(err_code);
}

void	ft_perror(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	set_prompt(void)
{
	char	*aux;

	g_shell->prompt = ft_strjoin(PROMPT1, g_shell->pwd);
	aux = g_shell->prompt;
	g_shell->prompt = ft_strjoin(aux, PROMPT2);
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
