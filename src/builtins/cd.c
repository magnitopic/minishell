/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:33:09 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/04 18:58:48 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * This functions updates the value on the env but only if it exists.
 * Used in the `cd` builtin to update `PWD` and `OLDPWD` values. When one of
 * these variables are removed 
*/
static void	mini_export(char *var, char *value)
{
	char	*aux;
	char	*aux_str;
	char	*substr;
	char	**env;

	aux_str = ft_strjoin(var, value);
	env = cpy_env(g_shell->env);
	while (*env)
	{
		aux = ft_strchr(*env, '=');
		if (aux)
			substr = ft_substr(*env, 0, ft_strlen(*env) - ft_strlen(aux));
		else
			substr = ft_strdup(*env);
		printf("%s -  %s\n", var, substr);
		if (ft_strcmp(var, substr) != 0)
		{
			*env = aux_str;
			break ;
		}
		env++;
	}
	free(g_shell->env);
	g_shell->env = env;
	free(aux_str);
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

static void	go_back(t_vars v, int num)
{
	v.len = ft_strlen(ft_strrchr(v.pwd, '/'));
	(free(v.pwd), v.pwd = NULL);
	v.pwd = ft_substr(v.pwd, 0, ft_strlen(v.pwd) - v.len);
	chdir(v.pwd);
	update_pwd();
	if (num != 0)
		exit(EXIT_SUCCESS);
}

static void	final_step(t_list *args, t_vars v, int num)
{
	v.aux = ft_strjoin(v.pwd, "/");
	v.pwd = ft_strjoin(v.aux, args->content);
	if (access(v.pwd, F_OK) == 0)
	{
		chdir(v.pwd);
		update_pwd();
		free(v.aux);
		free(v.pwd);
	}
	else
		perror("cd");
	if (num != 0)
		exit(EXIT_SUCCESS);
}

void	bi_cd(t_command *com, int num)
{
	t_list	*args;
	t_vars	v;

	args = com->args;
	v.pwd = g_shell->pwd;
	if (!args)
		return ;
	else if (access(args->content, F_OK) == 0)
	{
		chdir(args->content);
		update_pwd();
	}
	else if (args && ft_strncmp(args->content, "..", 2) == 0)
	{
		go_back(v, num);
		if (ft_strlen(args->content) == 2)
			return ;
	}
	final_step(args, v, num);
}
