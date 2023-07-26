/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:20:15 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/26 13:12:29 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	read_infile(t_redi *read)
{
	int	fd;
	
	fd = open(read->content, O_RDONLY);
	if (fd < 0)
		return ;
	dup2(fd, STDIN_FILENO);
	close(fd);
}
