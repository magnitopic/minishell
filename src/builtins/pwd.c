/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:33:22 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/07 14:14:42 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	bi_pwd(t_command *com)
{
	char	path[PATH_MAX];

	if (com->args)
		return (ft_putstr_fd("pwd: too many arguments\n", 2));
	printf("%s\n", getcwd(path, sizeof(path)));
}

/* int	main(int argc, char **argv)
{
	t_command	*test = malloc(sizeof(t_command));

	//ft_lstadd_new(&test->args, "There");
	bi_pwd(test);
	return (0);
} */
