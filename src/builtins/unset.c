/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:35:36 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/26 13:55:22 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* static int	find_in_env(char **env, char ***env_cpy, char *str)
{
	char	*substr;
	int		flag;
	int		i;

	i = 0;
	flag = -1;
	while (*env)
	{
		substr = ft_substr(*env, 0, \
		ft_strlen(*env) - ft_strlen(ft_strchr(*env, '=')));
		if (ft_strcmp(str, substr) == 0)
		{
			(*env_cpy)[i++] = *env++;
			flag = i;
		}
		free(substr);
	}
	return (flag);
} */

void	bi_unset(t_command *input, int num)
{
	t_list			*args;

	args = input->args;
	/* while (args)
	{
		find_in_env(env, args->content);
		args = args->next;
	} */
	if (num != 0)
		exit(EXIT_SUCCESS);
}

/* int	main(int argc, char **argv, char **env)
{
	t_command	*test = malloc(sizeof(t_command));

	ft_lstadd_new(&test->args, "_");
	bi_unset(test, &env, 0);
	bi_env(test, env, 0);
	return (0);
} */
