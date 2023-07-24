/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:33:22 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/24 17:05:23 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	bi_pwd(t_command *com, int num)
{
	char	path[PATH_MAX];

	if (com->args)
		return (ft_putstr_fd("pwd: too many arguments\n", 2));
	printf("%s\n", getcwd(path, sizeof(path)));
	if (num != 0)
		exit(EXIT_SUCCESS);
}

/* int	main(int argc, char **argv)
{
	t_command	*test = malloc(sizeof(t_command));

	//ft_lstadd_new(&test->args, "There");
	bi_pwd(test);
	return (0);
} */
