/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:32:55 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/29 16:19:40 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_program(int err_code)
{
	ft_putstr_fd("exit\n", 2);
	exit(err_code);
}

void	ft_perror(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

char	*set_prompt(void)
{
	char	*aux;
	char	*result;

	result = ft_strjoin(PROMPT1, g_shell->pwd);
	aux = result;
	result = ft_strjoin(result, PROMPT2);
	free(aux);
	return (result);
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
