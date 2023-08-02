/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:20:15 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/02 15:50:09 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	read_infile(t_redi *read, int num)
{
	int	fd;

	fd = open(read->content, O_RDONLY);
	if ((read->type == 0 && access(read->content, R_OK) != 0) || fd < 0)
	{
		ft_printf("\033[0;31mUnable to read file\033[0m\n");
		if (num != 0)
			exit(EXIT_FAILURE);
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (fd);
}

int	write_outfile(t_redi *write, int num)
{
	int	fd;

	if (write->type == 1)
		fd = open(write->content, O_TRUNC | O_WRONLY);
	else
		fd = open(write->content, O_APPEND | O_WRONLY);
	if (fd < 0)
	{
		ft_printf("\033[0;31mPermission denied\033[0m\n");
		if (num != 0)
			exit(EXIT_FAILURE);
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}
