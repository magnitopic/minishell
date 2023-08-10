/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:35:36 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/10 18:57:45 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	find_in_env(char **env, char ***env_cpy, char *str)
{
	char	*substr;
	char	*aux;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
	{
		aux = ft_strchr(env[i], '=');
		if (aux)
			substr = ft_substr(env[i], 0, ft_strlen(env[i]) - ft_strlen(aux));
		else
			substr = ft_strdup(env[i]);
		if (ft_strcmp(str, substr) != 0)
			(*env_cpy)[j++] = env[i];
		i++;
		free(substr);
	}
}

void	bi_unset(t_command *input, int num)
{
	t_list		*args;
	char		**env;
	char		**env_cpy;

	args = input->args;
	env = cpy_env(g_shell->env);
	while (args)
	{
		if (ft_strlen(args->content) != 0)
		{
			env_cpy = ft_calloc(ft_get_matrix_size(env) + 1, sizeof(char *));
			find_in_env(env, &env_cpy, args->content);
			free(env);
			env = env_cpy;
		}
		args = args->next;
	}
	free_matrix(g_shell->env);
	g_shell->env = env;
	g_shell->exit_stat = 0;
	if (num != 0)
		exit(EXIT_SUCCESS);
}
