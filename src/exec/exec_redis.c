/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:20:15 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/25 16:29:07 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	*read_infile(t_redi *read, int *fd)
{
	fd[0] = open(read->content, O_RDONLY);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (fd);
}
