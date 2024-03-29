/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:33:01 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/29 16:15:47 by alaparic         ###   ########.fr       */
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

static void	print_values(t_list *args)
{
	while (args)
	{
		ft_printf("%s", args->content);
		if (args->next && ft_strlen(args->content) > 0)
			ft_printf(" ");
		args = args->next;
	}
}

void	bi_echo(t_command *com, int num)
{
	t_list	*args;
	int		flag;
	int		n;

	flag = 1;
	n = 0;
	if (com->args && com->comm)
	{
		args = com->args;
		if (ft_strlen(args->content) > 1 && !ft_strncmp(args->content, "-", 1)
			&& ft_ischar(args->content, 'n') && n == 0)
		{
			flag = 0;
			args = args->next;
		}
		print_values(args);
		n++;
	}
	if (flag)
		ft_printf("\n");
	g_shell->exit_stat = 0;
	if (num != 0)
		exit(EXIT_SUCCESS);
}
