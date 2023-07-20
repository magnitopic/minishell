/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:27:28 by jsarabia          #+#    #+#             */
/*   Updated: 2023/07/20 17:51:05 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	read_infile(t_redi *read, int fd[2][2])
{
	fd[0][0] = open(read->content, O_RDONLY);
	dup2(fd[0][0], STDIN_FILENO);
	close(fd[0][0]);
	return (fd[0][0]);
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

void	execute_first(t_command *input, char **paths, char **env, t_files *files)
{
	if (input->redi && input->redi->type != 4)
		files = create_files(input, files);
	files->command = find_command(input->comm, paths);
	files->arr = set_for_execve(files, input);
	if (files->read->content)
		files->fd[0][0] = read_infile(files->read, files->fd);
	files->id[0] = fork();
	if (files->id[0] == 0)
	{
		if (files->write->content)
		{
			files->fd[0][1] = open(files->write->content, O_WRONLY);
			dup2(files->fd[0][1], 1);
			close(files->fd[0][1]);
		}
		else
		{
			dup2(files->fd[0][1], STDOUT_FILENO);
			close(files->fd[0][1]);
		}
		//close(files->fd[0]);
		//close(files->fd[1]);
		exec_cmd(input, files, env);
	}
	//close(files->fd[0][0]);
	//close(files->fd[0][1]);
}

void	execute_final(t_command *input, char **paths, char **env, t_files *files)
{
	if (files->fd[0][0] != 0)
	{
		dup2(files->fd[0][0], STDIN_FILENO);
		close(files->fd[0][0]);
		close(files->fd[0][1]);
	}
	if (input->redi && input->redi->type != 4)
		files = create_files(input, files);
	else
		files->write->content = NULL;
	files->command = find_command(input->comm, paths);
	files->arr = set_for_execve(files, input);
	if (files->read->content)
		files->fd[0][0] = read_infile(files->read, files->fd);
	files->id[files->count] = fork();
	if (files->id[files->count] == 0)
	{
		if (files->write->content)
		{
			files->fd[1][1] = open(files->write->content, O_WRONLY);
			dup2(files->fd[1][1], 1);
			close(files->fd[1][1]);
		}
		//close(files->fd[0]);
		//close(files->fd[1]);
		exec_cmd(input, files, env);
	}
	close(files->fd[0][0]);
	close(files->fd[0][1]);
	waitpid(files->id[files->count], NULL, 0);
}

/*
int	*execute_pipe(t_command *input, char **paths, char **env, t_files *files)
{
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
	//waitpid(files->id, NULL, 0);
	free(files->fd);
	return (fd);
}*/

void	exec(t_list *com, t_files *files, char **paths, char **env)
{
	t_list	*aux;

	aux = com;
	files->write = ft_calloc(1, sizeof(t_redi));
	files->read = ft_calloc(1, sizeof(t_redi));
	if (!com->next && check_builtin(com->content))
	{
		exec_one_builtin(com->content, files, env);
		com = NULL;
	}
	files->count = ft_lstsize(com);
	if (files->count == 1 && com)
	{
		execute_final(com->content, paths, env, files);
		com = NULL;
	}
	pipe(files->fd[0]);
	pipe(files->fd[1]);
	if (files->count == 2)
	{
		execute_first(com->content, paths, env, files);
		com = com->next;
		execute_final(com->content, paths, env, files);
		com = NULL;
	}
	while (com)
	{
		//print_commands(com->content, paths, env);
		/*files->fd = execute_final(com->content, paths, env, files);
		else*/
		if (!com->next)
			execute_final(com->content, paths, env, files);
		//ft_printf("holi\n");
		/*else
			files->fd = execute_pipe(com->content, paths, env, files);*/
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
