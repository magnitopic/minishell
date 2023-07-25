/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:27:28 by jsarabia          #+#    #+#             */
/*   Updated: 2023/07/25 15:47:26 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	*execute_first(t_command *input, char **paths, char **env, t_files *files)
{
	if (input->redi && input->redi->type != 4)
		files = create_files(input, files);
	else
	{
		files->write->content = NULL;
		files->read->content = NULL;
	}
	files->command = find_command(input->comm, paths);
	files->arr = set_for_execve(files, input);
	if (files->read->content)
		files->fd[0] = read_infile(files->read, files->fd);
	files->read->content = NULL;
	files->id[0] = fork();
	if (files->id[0] == 0)
	{
		if (files->write->content)
			files->fd[1] = open(files->write->content, O_WRONLY);
		dup2(files->fd[1], STDOUT_FILENO);
		close(files->fd[1]);
		exec_cmd(input, files, env, 1);
	}
	close(files->fd[1]);
	return (files->fd);
}

static void	execute_final(t_command *input, char **paths, char **env, t_files *files)
{
	if (files->fd[0] != 0)
	{
		dprintf(1, "infile: %s\n", files->read->content);
		dup2(files->fd[0], STDIN_FILENO);
		close(files->fd[0]);
	}
	if (input->redi && input->redi->type != 4)
		files = create_files(input, files);
	files->command = find_command(input->comm, paths);
	files->arr = set_for_execve(files, input);
	if (files->read->content)
		files->fd[0] = read_infile(files->read, files->fd);
	files->read->content = NULL;
	files->id[files->count] = fork();
	if (files->id[files->count] == 0)
	{
		if (files->write->content)
		{
			files->fd[1] = open(files->write->content, O_WRONLY);
			(dup2(files->fd[1], STDOUT_FILENO), close(files->fd[1]));
		}
		exec_cmd(input, files, env, 0);
	}
	close(files->fd[0]);
	waitpid(files->id[files->count], NULL, 0);
}

static int	*execute_pipes(t_command *input, char **paths, char **env, t_files *files)
{
	static int	i = 1;
	int			*fd;

	dup2(files->fd[0], STDIN_FILENO);
	close(files->fd[0]);
	fd = ft_calloc(2, sizeof(int));
	free(files->fd);
	if (input->redi && input->redi->type != 4)
		files = create_files(input, files);
	else
	{
		files->write->content = NULL;
		files->read->content = NULL;
	}
	files->command = find_command(input->comm, paths);
	files->arr = set_for_execve(files, input);
	if (files->read->content)
		files->fd[0] = read_infile(files->read, files->fd);
	files->read->content = NULL;
	pipe(fd);
	files->id[i] = fork();
	if (files->id[i++] == 0)
	{
		if (files->write->content)
			fd[1] = open(files->write->content, O_WRONLY);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_cmd(input, files, env, 1);
	}
	close(fd[1]);
	return (fd);
}

void	exec(t_list *com, t_files *files, char **paths, char **env)
{
	t_list	*aux;

	aux = com;
	files->fd = ft_calloc(2, sizeof(int));
	files->write = ft_calloc(1, sizeof(t_redi));
	files->read = ft_calloc(1, sizeof(t_redi));
	if ((!com->next && check_builtin(com->content)) || !com->content)
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
	pipe(files->fd);
	if (files->count == 2 && com)
	{
		files->fd = execute_first(com->content, paths, env, files);
		com = com->next;
		execute_final(com->content, paths, env, files);
		com = NULL;
	}
	else if (files->count > 2 && com)
	{
		files->fd = execute_first(com->content, paths, env, files);
		com = com->next;
		while (com->next)
		{
			files->fd = execute_pipes(com->content, paths, env, files);
			com = com->next;
		}
		execute_final(com->content, paths, env, files);
	}
	free_commands(aux);
}

/* static void	print_commands(t_command *input, char **paths, char **env)
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
