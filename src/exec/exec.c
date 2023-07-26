/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:27:28 by jsarabia          #+#    #+#             */
/*   Updated: 2023/07/26 17:53:26 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	*execute_first(t_command *input, char **paths, char **env, t_files *files)
{
	int	*fd;

	fd = files->fd;
	pipe(files->fd);
	files->id[0] = fork();
	if (files->id[0] == 0)
	{
		if (input->redi && input->redi->type != 4)
			files = create_files(input, files);
		else
		{
			files->write->content = NULL;
			files->read->content = NULL;
		}
		if (!files)
			return (fd);
		files->command = find_command(input->comm, paths);
		files->arr = set_for_execve(files, input);
		if (files->read->content)
			read_infile(files->read);
		files->read->content = NULL;
		if (files->write->content)
			write_outfile(files->write);
		else
		{
			dup2(files->fd[1], STDOUT_FILENO);
			close(files->fd[1]);
		}
		exec_cmd(input, files, env, 1);
	}
	close(files->fd[1]);
	//waitpid(files->id[0], NULL, 0);
	return (files->fd);
}

static void	execute_final(t_command *input, char **paths, char **env, t_files *files)
{
	files->id[files->count - 1] = fork();
	if (files->id[files->count - 1] == 0)
	{
		if (input->redi && input->redi->type != 4)
			files = create_files(input, files);
		else
		{
			files->write->content = NULL;
			files->read->content = NULL;
		}
		if (!files)
			return ;
		if (files->fd[0] != 0 && files->fd)
		{
			dup2(files->fd[0], STDIN_FILENO);
			close(files->fd[0]);
		}
		files->command = find_command(input->comm, paths);
		files->arr = set_for_execve(files, input);
		if (files->read->content)
			read_infile(files->read);
		files->read->content = NULL;
		if (files->write->content)
			write_outfile(files->write);
		exec_cmd(input, files, env, 0);
	}
	close(files->fd[0]);
	//waitpid(files->id[files->count - 1], NULL, 0);
}

static int	*execute_pipes(t_command *input, char **paths, char **env, t_files *files)
{
	static int	i = 1;
	int			*fd;

	fd = ft_calloc(2, sizeof(int));
	pipe(fd);
	files->id[i] = fork();
	if (files->id[i++] == 0)
	{
		if (input->redi && input->redi->type != 4)
			files = create_files(input, files);
		else
		{
			files->write->content = NULL;
			files->read->content = NULL;
		}
		if (!files)
			return (files->fd);
		if (files->fd[0] != 0 && files->fd)
		{
			dup2(files->fd[0], STDIN_FILENO);
			close(files->fd[0]);
		}
		files->command = find_command(input->comm, paths);
		files->arr = set_for_execve(files, input);
		if (files->read->content)
			read_infile(files->read);
		files->read->content = NULL;
		if (files->write->content)
			write_outfile(files->write);
		else
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		exec_cmd(input, files, env, 1);
	}
	close(fd[1]);
	free(files->fd);
	//waitpid(files->id[i - 1], NULL, 0);
	return (fd);
}

void	exec(t_list *com, t_files *files, char **paths, char **env)
{
	t_list	*aux;
	int		i;
	//int		status;

	aux = com;
	i = 0;
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
	//wait(&status);
	while (1)
	{
		if (waitpid(files->id[i++], NULL, 0) == -1)
			break ;
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