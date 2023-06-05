/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:17:52 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/05 12:29:58 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGQUIT)
		//exit_program("exit\n");
	if (sig == SIGINT)
	{
		printf("\n");
		// TODO: show prompt again
	}
}
