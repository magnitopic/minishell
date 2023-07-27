/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:35:36 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/27 11:46:19 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**find_in_env(char **env, char *str)
{
	char	*substr;
	int		i;
	int		j;
	char	**env_cpy;

	i = 0;
	j = 0;
	env_cpy = ft_calloc(ft_get_matrix_size(env), sizeof(char *));
	while (env[i])
	{
		substr = ft_substr(env[i], 0, \
		ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '=')));
		if (ft_strcmp(str, substr) != 0)
		{
			env_cpy[j] = env[i];
			j++;
		}
		i++;
		free(substr);
	}
	return (env_cpy);
}

void	bi_unset(t_command *input, int num)
{
	t_list		*args;
	char		**env;

	args = input->args;
	env = cpy_env(g_sl->env);
	while (args)
	{
		env = find_in_env(env, args->content);
		args = args->next;
	}
	free(g_sl->env);
	g_sl->env = env;
	if (num != 0)
		exit(EXIT_SUCCESS);
}
