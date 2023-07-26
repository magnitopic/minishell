/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:35:47 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/26 13:27:53 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	bi_env(t_command *com, int num)
{
	(void)com;
	ft_printmatrix(g_sl->env);
	if (num != 0)
		exit(EXIT_SUCCESS);
}

/* int	main(int argc, char **argv, char **env)
{
	t_command	*test = malloc(sizeof(t_command));

	//ft_lstadd_new(&test->args, "There");
	bi_env(test, env);
	return (0);
} */
