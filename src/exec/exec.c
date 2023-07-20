/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:27:28 by jsarabia          #+#    #+#             */
/*   Updated: 2023/07/20 16:17:12 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	*read_infile(t_redi *read, int *old_fd)
{
	int	*fd;

	if (old_fd)
		free(old_fd);
	fd = malloc(3 * sizeof(int));
	fd[0] = open(read->content, O_RDONLY);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (fd);
}

int	exec_cmd(t_command *input, t_files *files, char **env)
{
	if (!input->comm)
		return (0);
	if (ft_strcmp(input->comm, "cd") == 0)
		bi_cd(input, env);
	else if (ft_strcmp(input->comm, "echo") == 0)
		bi_echo(input);
	else if (ft_strcmp(input->comm, "env") == 0)
		bi_env(input, env);
	else if (ft_strcmp(input->comm, "exit") == 0)
		bi_exit(input);
	else if (ft_strcmp(input->comm, "export") == 0)
		bi_export(input, env);
	else if (ft_strcmp(input->comm, "pwd") == 0)
		bi_pwd(input);
	else if (ft_strcmp(input->comm, "unset") == 0)
		bi_unset(input, env);
	else if (files->command && access(files->command, F_OK) == 0)
		execve(files->command, files->arr, env);
	else
	{
		dup2(1, STDOUT_FILENO);
		ft_putstr_fd("\033[0;31mCommand not found\033[0m\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	return (0);
}

static int	check_builtin(t_command *input)
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

int	*execute_final(t_command *input, char **paths, char **env, t_files *files)
{
	if (files->fd[0] != 0)
	{
		dup2(files->fd[0], STDIN_FILENO);
		close(files->fd[0]);
		close(files->fd[1]);
	}
	((void)paths, (void)env);
	if (input->redi && input->redi->type != 4)
		files = create_files(input, files);
	files->command = find_command(input->comm, paths);
	files->arr = set_for_execve(files, input);
	if (files->read->content)
		files->fd = read_infile(files->read, files->fd);
	//if (!check_builtin(input) || files->fd[0] != 0)
	files->id = fork();
	if (files->id == 0)
	{
		if (files->write->content)
		{
			files->fd[1] = open(files->write->content, O_WRONLY);
			dup2(files->fd[1], 1);
			//close(files->fd[1]);
		}
		//close(files->fd[0]);
		//close(files->fd[1]);
		exec_cmd(input, files, env);
	}
	waitpid(files->id, NULL, 0);
	return (NULL);
}

int	*execute_pipe(t_command *input, char **paths, char **env, t_files *files)
{
	int	*fd;

	fd = ft_calloc(2, sizeof(int));
	if (files->fd[0] != 0)
	{
		dup2(files->fd[0], STDIN_FILENO);
		close(files->fd[0]);
		//close(files->fd[1]);
	}
	if (input->redi && input->redi->type != 4)
		files = create_files(input, files);
	files->command = find_command(input->comm, paths);
	files->arr = set_for_execve(files, input);
	pipe(fd);
	files->id = fork();
	if (files->id == 0)
	{
		if (files->write->content)
		{
			files->fd[1] = open(files->write->content, O_WRONLY);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			close(fd[0]);
		}
		else
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		if (exec_cmd(input, files, env))
			exit(EXIT_FAILURE);
	}
	//if (files->write->content)
	//close(files->fd[1]);
	//close(files->fd[0]);
	waitpid(files->id, NULL, 0);
	free(files->fd);
	return (fd);
}

void	exec(t_list *com, t_files *files, char **paths, char **env)
{
	t_list	*aux;
	int		num;

	aux = com;
	num = 1;
	files->fd = ft_calloc(3, sizeof(int));
	files->write = ft_calloc(1, sizeof(t_redi));
	files->read = ft_calloc(1, sizeof(t_redi));
	if (!com->next && check_builtin(com->content))
	{
		exec_one_builtin(com->content, files, env);
		com = NULL;
	}
	while (com)
	{
		//print_commands(com->content, paths, env);
		if (!com->next)
			num = 0;
		/*files->fd = execute_final(com->content, paths, env, files);
		else*/
		if (!com->next)
			files->fd = execute_final(com->content, paths, env, files);
		//ft_printf("holi\n");
		else
			files->fd = execute_pipe(com->content, paths, env, files);
		num = -1;
		com = com->next;
	}
	free_commands(aux);
}

/* void	print_commands(t_command *input, char **paths, char **env)
{
	t_redi	*aux;
	t_list	*aux_two;

	aux = input->redi;
	aux_two = input->args;
	((void)paths, (void)env);
	if (input->comm)
	{
		printf("command: %s\n", input->comm);
		//execute_one(&input->comm, paths, env);
	}
	while (aux)
	{
		printf("redi: %s\n", (char *)aux->content);
		printf("  -> type: %d\n", (int)aux->type);
		aux = aux->next;
	}
	while (aux_two)
	{
		printf("args: %s\n", (char *)aux_two->content);
		aux_two = aux_two->next;
	}
} */
