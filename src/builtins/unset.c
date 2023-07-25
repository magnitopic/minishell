/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:35:36 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/25 12:29:40 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	bi_unset(t_command *input, char ***env, int num)
{
	((void)input, (void)env);
	if (num != 0)
		exit(EXIT_SUCCESS);
	return ;
}
