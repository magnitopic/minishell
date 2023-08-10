/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:33:22 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/10 18:59:06 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	bi_pwd(t_command *com, int num)
{
	(void)com;
	/*if (com->args)
		return (ft_putstr_fd("pwd: too many arguments\n", 2));*/
	printf("%s\n", g_shell->pwd);
	g_shell->exit_stat = 0;
	if (num != 0)
		exit(EXIT_SUCCESS);
}
