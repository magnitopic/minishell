/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:33:37 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/10 19:10:16 by alaparic         ###   ########.fr       */
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

static int	find_in_env(char **env, char ***env_cpy, char *str)
{
	char	*substr;
	int		flag;
	int		i;
	char	*aux;

	i = 0;
	flag = -1;
	while (*env)
	{
		aux = ft_strchr(*env, '=');
		if (aux)
			substr = ft_substr(*env, 0, ft_strlen(*env) - ft_strlen(aux));
		else
			substr = ft_strdup(*env);
		if (ft_strcmp(str, substr) == 0)
			flag = i;
		free(substr);
		(*env_cpy)[i++] = *env++;
	}
	return (flag);
}

static char	**change_env(char **env, char *str, enum e_export flag)
{
	char	**new_env;
	char	*var;
	int		exists;
	char	*aux;

	new_env = ft_calloc(ft_get_matrix_size(env) + 2, sizeof(char *));
	aux = ft_strchr(str, '=');
	if (aux != 0)
		var = ft_substr(str, 0, ft_strlen(str) - ft_strlen(aux));
	else
		var = str;
	exists = find_in_env(env, &new_env, var);
	if (aux != 0)
		free(var);
	if (exists == -1)
	{
		new_env[ft_get_matrix_size(env)] = ft_strdup(str);
		free(env);
		env = new_env;
	}
	else if (flag == NEW_VALUE)
		env[exists] = str;
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

// TODO: Fix when multiple vars with same name
void	bi_export(t_command *input, int num)
{
	t_list			*args;
	enum e_export	result;
	char			**env;

	args = input->args;
	if (ft_lstsize(input->args) == 0)
		return (print_export(g_shell->env));
	while (args)
	{
		env = cpy_env(g_shell->env);
		result = validate(args->content);
		if (result == INVALID)
		{
			free_matrix(env);
			return (ft_putstr_fd("\033[0;31mInvalid identifier\n\033[0m", 0));
		}
		free_matrix(g_shell->env);
		g_shell->env = change_env(env, args->content, result);
		args = args->next;
	}
	g_shell->exit_stat = 0;
	if (num != 0)
		exit(EXIT_SUCCESS);
}
