/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:27:48 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/12 19:06:43 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ! Archivo temporal
#include "../../include/minishell.h"

char	**set_for_execve(t_files *files, t_command *input)
{
	char	**com_args;
	int		len;
	int		i;

	len = ft_lstsize(input->args);
	com_args = ft_calloc(len + 2, sizeof(char *));
	com_args[0] = files->command;
	i = 1;
	while (input->args)
	{
		com_args[i] = input->args->content;
		input->args = input->args->next;
		i++;
	}
	return (com_args);
}
