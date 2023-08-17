/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:35:44 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/17 17:06:08 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_num_input(char *arg)
{
	if (arg[0] == '-')
	{
		if (ft_strlen(arg) < ft_strlen("-9223372036854775808"))
			return (1);
		else if (ft_strlen(arg) > ft_strlen("-9223372036854775808"))
			return (0);
		else if (ft_strcmp(arg, "-9223372036854775808") <= 0)
			return (1);
		else if (ft_strcmp(arg, "-9223372036854775808") > 0)
			return (0);
	}
	if (ft_strlen(arg) < ft_strlen("9223372036854775807"))
		return (1);
	else if (ft_strlen(arg) > ft_strlen("9223372036854775807"))
		return (0);
	else if (ft_strcmp(arg, "9223372036854775807") <= 0)
		return (1);
	else if (ft_strcmp(arg, "9223372036854775807") > 0)
		return (0);
	return (0);
}

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
	{
		if (check_num_input(com->args->content))
			exit_program((unsigned int)ft_atoi(com->args->content));
		else
		{
			ft_putstr_fd("numeric argument required\n", 2);
			exit_program(255);
		}
	}
	else
		exit_program(EXIT_SUCCESS);
	if (num != 0)
		exit(EXIT_SUCCESS);
}
