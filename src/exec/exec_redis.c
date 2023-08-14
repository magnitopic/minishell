/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:20:15 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/14 15:24:58 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	read_infile(t_redi *read, int num, t_files *files, t_list *com)
{
	int	fd;

	fd = open(read->content, O_RDONLY);
	if ((read->type == 0 && access(read->content, R_OK) != 0) || fd < 0)
	{
		perror("MiniShell");
		close(fd);
		free_files(&files);
		if (num != 0)
		{
			free_files(&files);
			free_commands(&com);
			exit(EXIT_FAILURE);
		}
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (fd);
}

int	write_outfile(t_redi *write, int num, t_files *files, t_list *com)
{
	int	fd;

	if (write->type == 1)
		fd = open(write->content, O_TRUNC | O_WRONLY);
	else
		fd = open(write->content, O_APPEND | O_WRONLY);
	if (fd < 0)
	{
		ft_printf("\033[0;31mPermission denied\033[0m\n");
		close(fd);
		if (num != 0)
		{
			close(files->fd[1]);
			free_commands(&com);
			free_files(&files);
			exit(EXIT_FAILURE);
		}
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}
