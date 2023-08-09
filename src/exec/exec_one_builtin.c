/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:39:49 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/09 15:19:49 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_one_builtin(t_command *input, t_files *files, t_list *com)
{
	int	num;
	int	fd;

	num = 1;
	if (input->redi != NULL
		&& input->redi->type != 4)
	files = create_files(input, files, com);
	if (files->read->content)
		num = read_infile(files->read, 0, files, com);
	if (files->write->content)
		fd = write_outfile(files->write, 0, files);
	if (num != 0 && fd != -1)
		exec_cmd(input, files, 0);
}
