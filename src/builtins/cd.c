/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:33:09 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/31 16:54:33 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	go_home(t_vars v, int num)
{
	v.home = create_vars("HOME");
	chdir(v.home);
	free(v.home);
	if (num != 0)
		exit(EXIT_SUCCESS);
}

void	go_back(t_vars v, int num)
{
	v.len = ft_strlen(ft_strrchr(v.pwd, '/'));
	(free(v.pwd), v.pwd = NULL);
	v.pwd = ft_substr(v.pwd, 0, ft_strlen(v.pwd) - v.len);
	chdir(v.pwd);
	if (num != 0)
		exit(EXIT_SUCCESS);
}

void	final_step(t_list *args, t_vars v, int num)
{
	v.aux = ft_strjoin(v.pwd, "/");
	v.pwd = ft_strjoin(v.aux, args->content);
	if (access(v.pwd, F_OK) == 0)
	{
		chdir(v.pwd);
		free(v.aux);
		free(v.pwd);
	}
	else
		perror("cd");
	if (num != 0)
		exit(EXIT_SUCCESS);
}

void	bi_cd(t_command *com, int num)
{
	char	path[PATH_MAX];
	t_list	*args;
	t_vars	v;

	args = com->args;
	v.pwd = getcwd(path, sizeof(path));
	if (!args)
	{
		go_home(v, num);
		return ;
	}
	else if (access(args->content, F_OK) == 0)
		chdir(args->content);
	else if (args && ft_strncmp(args->content, "..", 2) == 0)
	{
		go_back(v, num);
		if (ft_strlen(args->content) == 2)
			return ;
	}
	final_step(args, v, num);
}
