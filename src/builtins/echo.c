/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:33:01 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/24 18:43:59 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_ischar(char *str, char c)
{
	int	n;

	n = 1;
	if (!str[1])
		return (0);
	while (str[n])
	{
		if (str[n] != c)
			return (0);
		n++;
	}
	return (1);
}

void	bi_echo(t_command *com, int num)
{
	t_list	*args;
	int		flag;

	if (!com->args || ft_strlen(com->args->content) < 1)
		return (ft_putstr_fd("\n", 1));
	args = com->args;
	if (ft_strlen(args->content) > 1 && !ft_strncmp(args->content, "-", 1)
		&& ft_ischar(args->content, 'n'))
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
	if (num != 0)
		exit(EXIT_SUCCESS);
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
