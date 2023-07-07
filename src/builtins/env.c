/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:35:47 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/07 15:17:07 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	bi_env(t_command *com, char **env)
{
	(void)com;
	ft_printmatrix(env);
}

/* int	main(int argc, char **argv, char **env)
{
	t_command	*test = malloc(sizeof(t_command));

	//ft_lstadd_new(&test->args, "There");
	bi_env(test, env);
	return (0);
} */
