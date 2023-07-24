/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:33:37 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/24 11:47:36 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_export(char **env)
{
	int		i;
	char	**sort_env;

	i = 0;
	sort_env = ft_sort_matrix(env);
	while (sort_env[i])
		ft_printf("declare -x %s\n", sort_env[i++]);
}
/* 
static char	**add_to_env(char **env, char *str)
{
	char	**new_env;
	char	**aux;
	int		i;

	i = 0;
	aux = env;
	new_env = ft_calloc(ft_get_matrix_size(env) + 2, sizeof(char *));
	while (*env)
		new_env[i++] = *env++;
	new_env[i] = str;
	free(aux);
	return (new_env);
} */

static void	add_to_env(char **env, char *str)
{
	char	*substr;
	int		flag;

	(void)str;
	flag = 1;
	while (*env)
	{
		substr = ft_substr(*env, 0, \
		ft_strlen(*env) - ft_strlen(ft_strchr(*env, '=')));
		if (ft_strcmp(str, substr) == 0)
			flag = 0;
		free(substr);
		env++;
	}
	if (flag)
		
}

static enum e_export	validate(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '=')
	{
		if (i == 0 && !(ft_isalpha(str[i]) || str[i] == '_'))
			return (INVALID);
		else if (i != 0 && !(ft_isalnum(str[i]) || str[i] == '_'))
			return (INVALID);
	}
	if (str[i] == '\0')
		return (CREATE);
	return (NEW_VALUE);
}

void	bi_export(t_command *input, char **env)
{
	t_list			*args;
	enum e_export	result;

	args = input->args;
	if (ft_lstsize(input->args) == 0)
		return (print_export(env));
	while (args)
	{
		result = validate(args->content);
		if (result == INVALID)
			return (ft_putstr_fd("\033[0;31mInvalid identifier\n\033[0m", 0));
		/* if (result == NEW_VALUE)
			replace_in_env(env, args->content); */
		if (result == CREATE)
			add_to_env(env, args->content);
		args = args->next;
	}
	return ;
}

int	main(int argc, char **argv, char **env)
{
	
	t_command	*test = malloc(sizeof(t_command));

	ft_lstadd_new(&test->args, "There");
	bi_export(test, env);
	return (0);
}
