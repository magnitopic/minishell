/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:33:09 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/07 13:06:10 by alaparic         ###   ########.fr       */
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
	char	*substr;
	char	**env;
	char	**aux;

	value = ft_strjoin(var, value);
	env = cpy_env(g_shell->env);
	aux = env;
	printf("%s -  %s\n", var, value);
	while (*env)
	{
		substr = ft_strchr(*env, '=');
		if (substr)
			substr = ft_substr(*env, 0, ft_strlen(*env) - ft_strlen(substr));
		else
			substr = ft_strdup(*env);
		printf("yes: %s\n", substr);
		printf("value: %d\n", ft_strcmp(var, substr) != 0);
		if (ft_strcmp(var, substr) == 0)
		{
			*env = value;
			break ;
		}
		env++;
	}
	//free(g_shell->env);
	g_shell->env = aux;
	free(substr);
}

static void	update_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
	{
		mini_export("OLDPWD", g_shell->pwd);
		g_shell->pwd = ft_strdup(getcwd(path, sizeof(path)));
		mini_export("PWD", g_shell->pwd);
	}
}

void	bi_cd(t_command *com, int num)
{
	t_list	*args;
	char	*pwd;
	char	*aux;
	int		stat;

	args = com->args;
	pwd = g_shell->pwd;
	if (!args)
		return ;
	aux = ft_strjoin(pwd, "/");
	pwd = ft_strjoin(aux, args->content);
	stat = chdir(pwd);
	if (!stat)
		update_pwd();
	else
		perror("cd");
	free(aux);
	free(pwd);
	if (num != 0)
		exit(EXIT_SUCCESS);
}
