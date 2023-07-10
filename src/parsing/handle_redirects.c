/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:20:52 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/10 16:03:02 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

enum e_redirect	handle_redirects(char *str)
{
	if (ft_strncmp(str, "<", 1) == 0 && ft_strlen(str) == 1)
		return (INPUT);
	if (ft_strncmp(str, ">", 1) == 0 && ft_strlen(str) == 1)
		return (OUTPUT);
	if (ft_strncmp(str, "<<", 2) == 0 && ft_strlen(str) == 2)
		return (HEREDOC);
	if (ft_strncmp(str, ">>", 2) == 0 && ft_strlen(str) == 2)
		return (APPEND);
	else
		return (BAD_INPUT);
}
