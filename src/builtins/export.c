/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:33:37 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/18 19:05:34 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

typedef struct s_test
{
	char	*before;
	char	*after;
}	t_test;

static void	print_export(char **env)
{
	int		i;
	char	**sort_env;

	i = 0;
	sort_env = ft_sort_matrix(env);
	while (sort_env[i])
		ft_printf("declare -x %s\n", sort_env[i++]);
}

static t_test	*validate(char *test)
{
	char	*str;
	t_test	*variable;

	str = ft_strchr(test, '=');
	if (str == NULL)
		return (free(str), NULL);
	variable = ft_calloc(1, sizeof(t_test));
	if (ft_strlen(str) > 1)
		ft_strlcpy(variable->after, str , ft_strlen(str));
	printf("%s\n", ft_substr(test, 0, ft_strlen(test) - ft_strlen(str)));
	variable->after = ft_substr(test, 0, ft_strlen(test) - ft_strlen(str) - 1);
	return (variable);
}

void	bi_export(t_command *input, char **env)
{
	t_list	*args;

	args = input->args;
	if (ft_lstsize(input->args) == 0)
		return (print_export(env));
	while (args)
	{
		if (validate(args->content) == NULL)
			return (ft_putstr_fd("\033[0;31mInvalid identifier\n\033[0m", 0));
		args = args->next;
	}
	return ;
}

/* int	main(int argc, char **argv, char **env)
{
	t_command	*test = malloc(sizeof(t_command));

	ft_lstadd_new(&test->args, "There=dfg");
	bi_export(test, env);
	return (0);
} */
