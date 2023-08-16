/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:35:44 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/16 12:26:14 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	bi_exit(t_command *com, int num)
{
	if (com->args && !ft_str_isdigit(com->args->content))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit_program(255);
	}
	else if (com->args && com->args->next)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_shell->exit_stat = 1;
	}
	else if (com->args && ft_str_isdigit(com->args->content))
		exit_program((unsigned int)ft_atoi(com->args->content));
	else
		exit_program(EXIT_SUCCESS);
	if (num != 0)
		exit(EXIT_SUCCESS);
}
