/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:32:55 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/08 12:44:52 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_program(char *message)
{
	printf("%s", message);
	free(g_shell->prompt);
	exit (0);
}

void	set_prompt(void)
{
	char	*aux;
	char	path[PATH_MAX];

	g_shell->prompt = ft_strjoin(PROMPT1, getcwd(path, sizeof(path)));
	aux = g_shell->prompt;
	g_shell->prompt = ft_strjoin(aux, PROMPT2);
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
