/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:39:49 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/31 17:26:42 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_one_builtin(t_command *input, t_files *files)
{
	int	num;

	num =  1;
	if (input->redi != NULL
		&& input->redi->type != 4)
	files = create_files(input, files);
	if (files->read->content)
		num = read_infile(files->read, 0);
	if (files->write->content)
		write_outfile(files->write);
	if (num != 0)
		exec_cmd(input, files, 0);
}
