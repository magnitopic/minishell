/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:33:37 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/24 14:54:48 by alaparic         ###   ########.fr       */
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

static int	find_in_env(char **env, char ***env_cpy, char *str)
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
			flag = i;
		free(substr);
		(*env_cpy)[i++] = *env++;
	}
	return (flag);
}

static char	**replace_in_env(char **env, char *str)
{
	char	**new_env;
	char	*var;
	int		flag;

	new_env = ft_calloc(ft_get_matrix_size(env) + 2, sizeof(char *));
	var = ft_substr(str, 0, ft_strlen(str) - ft_strlen(ft_strchr(str, '=')));
	flag = find_in_env(env, &new_env, var);
	if (flag != -1)
		env[flag] = str;
	else
	{
		new_env[ft_get_matrix_size(env)] = str;
		env = new_env;
	}
	return (env);
}

static char	**add_to_env(char **env, char *str)
{
	char	**new_env;
	int		flag;

	new_env = ft_calloc(ft_get_matrix_size(env) + 2, sizeof(char *));
	flag = find_in_env(env, &new_env, str);
	if (flag == -1)
	{
		new_env[ft_get_matrix_size(env)] = str;
		env = new_env;
	}
	return (env);
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

void	bi_export(t_command *input, char ***env)
{
	t_list			*args;
	enum e_export	result;

	args = input->args;
	if (ft_lstsize(input->args) == 0)
		return (print_export(*env));
	while (args)
	{
		result = validate(args->content);
		if (result == INVALID)
			return (ft_putstr_fd("\033[0;31mInvalid identifier\n\033[0m", 0));
		if (result == NEW_VALUE)
			*env = replace_in_env(*env, args->content);
		if (result == CREATE)
			*env = add_to_env(*env, args->content);
		args = args->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_command	*test = malloc(sizeof(t_command));

	((void)argc, (void)argv);
	ft_lstadd_new(&test->args, "hi=There");
	bi_export(test, &env);
	bi_env(test, env);
	return (0);
}
