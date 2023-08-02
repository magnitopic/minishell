/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:27:28 by jsarabia          #+#    #+#             */
/*   Updated: 2023/08/02 17:19:43 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_files	*execute_first(t_command *input, t_files *files)
{
	pipe(files->fd);
	ft_lstadd_new(&files->file_d, files->fd);
	files->id[0] = fork();
	if (files->id[0] == 0)
	{
		close(files->fd[0]);
		if (input->redi && input->redi->type != 4)
			files = create_files(input, files);
		if (!files)
			return (files);
		files->command = find_command(input->comm);
		files->arr = set_for_execve(files, input);
		if (files->read->content)
			read_infile(files->read, 1);
		files->read->content = NULL;
		if (files->write->content)
			write_outfile(files->write, 1);
		else
			(dup2(files->fd[1], STDOUT_FILENO), close(files->fd[1]));
		exec_cmd(input, files, 1);
	}
	close(files->fd[1]);
	return (files);
}

t_files	*execute_final(t_command *input, t_files *files)
{
	files->id[files->count - 1] = fork();
	if (files->id[files->count - 1] == 0)
	{
		if (input->redi && input->redi->type != 4)
			files = create_files(input, files);
		if (!files)
			return (NULL);
		if (files->fd[0] != 0 && files->fd)
			(dup2(files->fd[0], STDIN_FILENO), close(files->fd[0]));
		files->command = find_command(input->comm);
		files->arr = set_for_execve(files, input);
		if (files->read->content)
			read_infile(files->read, 1);
		files->read->content = NULL;
		if (files->write->content)
			write_outfile(files->write, 1);
		exec_cmd(input, files, 1);
	}
	close(files->fd[0]);
	close(files->fd[1]);
	return (files);
}

t_files	*execute_pipes(t_command *input, t_files *files, int i)
{
	int			*fd;

	fd = ft_calloc(2, sizeof(int));
	pipe(fd);
	files->id[i] = fork();
	if (files->id[i++] == 0)
	{
		close(fd[0]);
		if (input->redi && input->redi->type != 4)
			files = create_files(input, files);
		if (!files)
			return (files);
		if (files->fd[0] != 0)
			(dup2(files->fd[0], STDIN_FILENO), close(files->fd[0]));
		files->command = find_command(input->comm);
		files->arr = set_for_execve(files, input);
		if (files->read->content)
			read_infile(files->read, 1);
		files->read->content = NULL;
		if (files->write->content)
			write_outfile(files->write, 1);
		else
			(dup2(fd[1], STDOUT_FILENO), close(fd[1]));
		exec_cmd(input, files, 1);
	}
	close(fd[1]);
	close(files->fd[0]);
	files->fd = fd;
	return (files);
}

void	wait_function(t_files *files)
{
	int		i;
	int		status;
	pid_t	result;

	i = 0;
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		result = waitpid(files->id[i++], &status, 0);
		if (result == -1)
		{
			if (errno == ECHILD)
				break ;
			perror("waitpid");
			break ;
		}
	}
	if (WIFEXITED(status))
		g_shell->exit_stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_shell->exit_stat = WTERMSIG(status) + 128;
	else
		g_shell->exit_stat = 1;
	signal(SIGINT, signal_handler);
}

void	exec(t_list *com, t_files *files)
{
	t_list	*aux;
	int		i;

	i = 1;
	aux = com;
	files->fd = ft_calloc(2, sizeof(int));
	files->write = ft_calloc(1, sizeof(t_redi));
	files->read = ft_calloc(1, sizeof(t_redi));
	files->count = ft_lstsize(com);
	if ((!com->next && check_builtin(com->content)) || !com->content)
		exec_one_builtin(com->content, files);
	else if (files->count == 1)
		execute_final(com->content, files);
	else if (files->count == 2)
	{
		files = execute_first(com->content, files);
		com = com->next;
		execute_final(com->content, files);
	}
	else if (files->count > 2)
	{
		files = execute_first(com->content, files);
		com = com->next;
		while (com->next)
		{
			files = execute_pipes(com->content, files, i);
			i++;
			com = com->next;
		}
		execute_final(com->content, files);
	}
	wait_function(files);
	there_doc();
	free_commands(aux);
	free_files(files);
}

/* static void	print_commands(t_command *input)
{
	t_redi	*aux;
	t_list	*aux_two;

	aux = input->redi;
	aux_two = input->args;
	if (input->comm)
	{
		printf("command: %s\n", input->comm);
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
