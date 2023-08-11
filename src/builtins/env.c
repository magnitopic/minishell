/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:35:47 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/11 12:15:14 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	bi_env(t_command *com, int num)
{
	if (com->args)
	{
		ft_putstr_fd("env: Takes no arguments\n", 2);
		g_shell->exit_stat = 127;
	}
	else
	{
		ft_printmatrix(g_shell->env);
		g_shell->exit_stat = 0;
	}
	if (num != 0)
		exit(EXIT_SUCCESS);
}
