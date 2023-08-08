/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 19:53:35 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/07 19:53:57 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_files(t_files *file)
{
	if (file == NULL)
		return ;
	free_redi(&file->write);
	free_redi(&file->read);
	//free_matrix(file->arr);
	free(file->fd);
	free(file);
}

void	free_redi(t_redi **redi)
{
	if (*redi == NULL)
		return ;
	if ((*redi)->next != NULL)
		free_redi(&(*redi)->next);
	(free(*redi), *redi = NULL);
}

void	free_commands(t_list *cmd)
{
	t_list		*input;
	t_command	*command;

	input = cmd;
	while (input)
	{
		command = input->content;
		if (command->args != NULL)
			free_lists(&(command->args));
		if (command->redi != NULL)
			free_redi(&command->redi);
		if (command->comm != NULL)
			free(command->comm);
		free(command);
		input = input->next;
	}
	free(cmd);
}

void	free_lists(t_list **list)
{
	if (*list == NULL)
		return ;
	if ((*list)->next != NULL)
		free_lists(&(*list)->next);
	(free(*list), *list = NULL);
}

void	free_tokens(t_tokens **list)
{
	if (*list == NULL)
		return ;
	if ((*list)->next != NULL)
		free_tokens(&(*list)->next);
	(free(*list), *list = NULL);
}
