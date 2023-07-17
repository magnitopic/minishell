/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:33:01 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/17 17:32:51 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	bi_echo(t_command *com)
{
	t_list	*args;
	int		flag;

	if (!com->args || ft_strlen(com->args->content) < 1)
		return (ft_putstr_fd("\n", 1));
	args = com->args;
	if (!ft_strncmp(args->content, "-n", ft_strlen(args->content)))
	{
		flag = 0;
		args = args->next;
	}
	else
		flag = 1;
	while (args)
	{
		ft_printf("%s", args->content);
		if (args->next)
			ft_printf(" ");
		args = args->next;
	}
	if (flag)
		ft_printf("\n");
}

/* int	main(int argc, char **argv)
{
	t_command *test = malloc(sizeof(t_command));

	ft_lstadd_new(&test->args, "-n");
	ft_lstadd_new(&test->args, "Hello");
	ft_lstadd_new(&test->args, "There");
	bi_echo(test);
	return (0);
} */
