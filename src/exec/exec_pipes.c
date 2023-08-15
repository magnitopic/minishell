/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:07:47 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/15 15:14:29 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_files	*execute_first(t_command *in, t_files *fil, t_list *com)
{
	pipe(fil->fd);
	fil->id[0] = fork();
	if (fil->id[0] == 0)
	{
		close(fil->fd[0]);
		if (in->redi && in->redi->type != 4)
			fil = create_files(in, fil);
		if (!fil)
			return (fil);
		fil->command = find_command(in->comm);
		fil->arr = set_for_execve(fil, in);
		if (fil->read->content)
		{
			read_infile(fil->read, 1, fil, com);
			free(fil->read->content);
		}
		fil->read->content = NULL;
		if (fil->write->content)
			write_outfile(fil->write, 1, fil, com);
		else
			(dup2(fil->fd[1], STDOUT_FILENO), close(fil->fd[1]));
		exec_cmd(in, fil, 1);
	}
	close(fil->fd[1]);
	return (fil);
}

t_files	*execute_final(t_command *in, t_files *fil, t_list *com)
{
	fil->id[fil->count - 1] = fork();
	if (fil->id[fil->count - 1] == 0)
	{
		if (in->redi && in->redi->type != 4)
			fil = create_files(in, fil);
		if (!fil)
			return (NULL);
		if (fil->fd[0] != 0 && fil->fd)
			(dup2(fil->fd[0], STDIN_FILENO), close(fil->fd[0]));
		fil->command = find_command(in->comm);
		fil->arr = set_for_execve(fil, in);
		if (fil->read->content)
		{
			read_infile(fil->read, 1, fil, com);
			free(fil->read->content);
		}
		fil->read->content = NULL;
		if (fil->write->content)
			write_outfile(fil->write, 1, fil, com);
		exec_cmd(in, fil, 1);
	}
	close(fil->fd[0]);
	close(fil->fd[1]);
	return (fil);
}

int	exec_pipes_child(t_command *in, t_files *fil, t_list *com, int *fd)
{
	close(fd[0]);
	if (in->redi && in->redi->type != 4)
		fil = create_files(in, fil);
	if (!fil)
		return (0);
	if (fil->fd[0] != 0)
		(dup2(fil->fd[0], STDIN_FILENO), close(fil->fd[0]));
	fil->command = find_command(in->comm);
	fil->arr = set_for_execve(fil, in);
	if (fil->read->content)
	{
		read_infile(fil->read, 1, fil, com);
		free(fil->write->content);
	}
	fil->read->content = NULL;
	if (fil->write->content)
		write_outfile(fil->write, 1, fil, com);
	else
		(dup2(fd[1], STDOUT_FILENO), close(fd[1]));
	exec_cmd(in, fil, 1);
	return (1);
}

t_files	*execute_pipes(t_command *in, t_files *fil, int i, t_list *com)
{
	int			*fd;

	fd = ft_calloc(2, sizeof(int));
	pipe(fd);
	fil->id[i] = fork();
	if (fil->id[i++] == 0)
	{
		if (!exec_pipes_child(in, fil, com, fd))
			return (fil);
	}
	close(fd[1]);
	close(fil->fd[0]);
	free(fil->fd);
	fil->fd = fd;
	return (fil);
}
