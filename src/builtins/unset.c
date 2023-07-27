/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:35:36 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/26 19:43:43 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**find_in_env(char **env, char *str)
{
	char	*substr;
	int		i;
	char	*env_cpy;

	i = 0;
	env_cpy = ft_calloc(ft_get_matrix_size(env), sizeof(char *));
	while (*env)
	{
		substr = ft_substr(*env, 0, \
		ft_strlen(*env) - ft_strlen(ft_strchr(*env, '=')));
		if (ft_strcmp(str, substr) == 0)
		{
			env_cpy[i] = env[i++];
		}
		free(substr);
	}
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

int	main(int argc, char **argv, char **env)
{
	t_command	*test = malloc(sizeof(t_command));

	g_sl = ft_calloc(1, sizeof(t_shell));
	g_sl->env = cpy_env(env);
	ft_lstadd_new(&test->args, "_");
	bi_unset(test, 0);
	bi_env(test, 0);
	return (0);
}
