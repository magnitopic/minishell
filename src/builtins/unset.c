/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:35:36 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/27 12:42:58 by alaparic         ###   ########.fr       */
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
		{
			(*env_cpy)[j] = env[i];
			j++;
		}
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
	env = cpy_env(g_sl->env);
	while (args)
	{
		env_cpy = ft_calloc(ft_get_matrix_size(env), sizeof(char *));
		find_in_env(env, &env_cpy, args->content);
		free(env);
		env = env_cpy;
		args = args->next;
	}
	free(g_sl->env);
	g_sl->env = env;
	if (num != 0)
		exit(EXIT_SUCCESS);
}
