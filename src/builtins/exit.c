/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:35:44 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/10 19:09:21 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: Añadir a la libft
int	ft_str_isdigit(char *str)
{
	int	n;

	n = 0;
	while (str[n])
	{
		if (!ft_isdigit(str[n]))
			return (0);
		n++;
	}
	return (1);
}

void	bi_exit(t_command *com, int num)
{
	if (com->args && !ft_str_isdigit(com->args->content))
		exit_program("exit: numeric argument required\n", 255);
	else if (com->args && com->args->next)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_shell->exit_stat = 1;
	}
	else if (com->args && ft_str_isdigit(com->args->content))
		exit_program("exit\n", ft_atoi(com->args->content));
	else
		exit_program("exit\n", EXIT_SUCCESS);
	if (num != 0)
		exit(EXIT_SUCCESS);
}
