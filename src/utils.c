/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:32:55 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/26 12:28:52 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_program(char *message)
{
	printf("%s", message);
	exit(EXIT_SUCCESS);
}

void	ft_perror(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	set_prompt(void)
{
	char	*aux;
	char	path[PATH_MAX];

	g_sl->prompt = ft_strjoin(PROMPT1, getcwd(path, sizeof(path)));
	aux = g_sl->prompt;
	g_sl->prompt = ft_strjoin(aux, PROMPT2);
	free(aux);
}

void	free_stacks(t_list **list)
{
	if (*list == NULL)
		return ;
	if ((*list)->next != NULL)
		free_stacks(&(*list)->next);
	(free(*list), *list = NULL);
}

void	free_commands(t_list *cmd)
{
	t_list		*input;
	t_command	*command;

	input = cmd;
	while (input)
	{
		command = input->content;
		if (command == NULL)
			return ;
		if (command->args != NULL)
			free_stacks(&(command->args));
		/* if (command->redi != NULL)
			free_stacks(&(command->redi)); */
		free(command);
		input = input->next;
	}
	free(cmd);
}
