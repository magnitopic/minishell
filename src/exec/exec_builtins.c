/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:27:44 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/31 11:49:40 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		exit(EXIT_FAILURE);
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
