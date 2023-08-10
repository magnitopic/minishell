/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:27:44 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/10 18:58:31 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_path(char *str, char **paths)
{
	int		n;
	char	*temp;
	char	*aux;

	n = 0;
	if (!paths)
		return (1);
	while (paths[n])
	{
		temp = ft_strjoin(paths[n], "/");
		aux =  ft_strjoin(temp, str);
		if (access(aux, F_OK) == 0)
		{
			free(temp);
			free(aux);
			return (0);
		}
		free(temp);
		free(aux);
		n++;
	}
	return (1);
}

int	exec_cmd(t_command *input, t_files *files, int flag)
{
	if (!input->comm)
		bi_echo(input, flag);
	else if (ft_strcmp(input->comm, "cd") == 0)
		bi_cd(input, flag);
	else if (ft_strcmp(input->comm, "echo") == 0)
		bi_echo(input, flag);
	else if (ft_strcmp(input->comm, "env") == 0)
		bi_env(input, flag);
	else if (ft_strcmp(input->comm, "exit") == 0)
		bi_exit(input, flag);
	else if (ft_strcmp(input->comm, "export") == 0)
		bi_export(input, flag);
	else if (ft_strcmp(input->comm, "pwd") == 0)
		bi_pwd(input, flag);
	else if (ft_strcmp(input->comm, "unset") == 0)
		bi_unset(input, flag);
	else
	{
		execve(files->command, files->arr, g_shell->env);
		dup2(1, STDOUT_FILENO);
		ft_putstr_fd("\033[0;31mCommand not found\033[0m\n", STDERR_FILENO);
		exit(127);
	}
	return (0);
}

int	check_builtin(t_command *input)
{
	if (!input->comm)
		return (1);
	if (ft_strcmp(input->comm, "cd") == 0)
		return (1);
	else if (ft_strcmp(input->comm, "echo") == 0)
		return (1);
	else if (ft_strcmp(input->comm, "env") == 0)
		return (1);
	else if (ft_strcmp(input->comm, "exit") == 0)
		return (1);
	else if (ft_strcmp(input->comm, "export") == 0)
		return (1);
	else if (ft_strcmp(input->comm, "pwd") == 0)
		return (1);
	else if (ft_strcmp(input->comm, "unset") == 0)
		return (1);
	return (0);
}

int	check_builtin_str(char *str)
{
	if (!str)
		return (1);
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	return (0);
}
