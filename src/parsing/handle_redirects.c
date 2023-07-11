/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:20:52 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/11 13:10:57 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Classify what type of redirect has been input
*/
enum e_redirect	flag_redi(char *str)
{
	if (!ft_strncmp(str, "<", 1) && ft_strlen(str) == 1)
		return (INPUT);
	if (!ft_strncmp(str, ">", 1) && ft_strlen(str) == 1)
		return (OUTPUT);
	if (!ft_strncmp(str, "<<", 2) && ft_strlen(str) == 2)
		return (HEREDOC);
	if (!ft_strncmp(str, ">>", 2) && ft_strlen(str) == 2)
		return (APPEND);
	else
		return (BAD_INPUT);
}

void	handle_redirects(char *str, t_redi **redi, t_list **tokens)
{
	enum e_redirect	flag;

	printf("STR: %s\n", str);
	flag = flag_redi(str);
	if (flag == BAD_INPUT)
		exit(EXIT_FAILURE); // TODO: hacer una función que salga del programa dando error
	if ((*tokens)->next == NULL)
	{
		str = (*tokens)->next->content;
		*tokens = (*tokens)->next;
	}
	else
		str = ft_calloc(1, 1);
	if (flag == HEREDOC)
		str = heredoc(str);
	ft_newcommand(redi, str, flag);
}
