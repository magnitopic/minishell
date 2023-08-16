/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:33:09 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/16 15:23:10 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * This functions updates the value on the env but only if it exists.
 * Used in the `cd` builtin to update `PWD` and `OLDPWD` values. If one of the
 * variables is unset, it's value in not updated.
*/
static void	mini_export(char *var, char *value)
{
	char	*subst;
	char	**env;
	char	**aux;

	value = ft_strjoin(var, value);
	env = cpy_env(g_shell->env);
	aux = env;
	subst = "";
	while (*env)
	{
		subst = ft_strchr(*env, '=');
		if (subst)
			subst = ft_substr(*env, 0, ft_strlen(*env) - ft_strlen(subst) + 1);
		else
			subst = ft_strdup(*env);
		if (ft_strcmp(var, subst) == 0)
		{
			free(*env);
			*env = ft_strdup(value);
		}
		free(subst);
		env++;
	}
	(free(value), free_matrix(g_shell->env));
	g_shell->env = aux;
}

static void	update_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
	{
		mini_export("OLDPWD=", g_shell->pwd);
		free(g_shell->pwd);
		g_shell->pwd = ft_strdup(getcwd(path, sizeof(path)));
		mini_export("PWD=", g_shell->pwd);
	}
}

char	*get_route(char *str)
{
	char	*aux;
	char	*pwd;

	if (!access(str, F_OK))
		return (ft_strdup(str));
	aux = ft_strjoin(g_shell->pwd, "/");
	pwd = ft_strjoin(aux, str);
	free(aux);
	return (pwd);
}

void	bi_cd(t_command *com, int num)
{
	t_list	*args;
	char	*pwd;
	int		stat;

	args = com->args;
	if (!args)
		return ;
	pwd = get_route(args->content);
	stat = chdir(pwd);
	if (!stat)
	{
		g_shell->exit_stat = 0;
		update_pwd();
	}
	else
	{
		g_shell->exit_stat = 1;
		perror("cd");
	}
	free(pwd);
	if (num != 0)
		exit(EXIT_SUCCESS);
}
