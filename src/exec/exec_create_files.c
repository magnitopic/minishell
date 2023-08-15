/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_create_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:17:40 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/15 16:08:55 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_files	*check_files(t_files *files, char *name, int flag)
{
	if (access(name, F_OK))
		open(name, O_CREAT, 0644);
	if (flag == 1)
		open(name, O_TRUNC);
	if (open(name, O_WRONLY) < 0)
	{
		g_shell->exit_stat = 1;
		perror("MiniShell:");
		return (NULL);
	}
	if (files->write->content)
		free(files->write->content);
	files->write->content = ft_substr(name, 0, ft_strlen(name));
	files->write->type = flag;
	return (files);
}

char	*find_name_com(char **paths, char **paths_aux, char *aux, char *argv)
{
	char	*str;
	char	*temp;

	str = NULL;
	temp = NULL;
	while (*paths != NULL)
	{
		if (access(argv, F_OK) == 0 && argv[0] == '/')
			return (free_matrix(paths_aux), argv);
		aux = ft_strjoin(*paths, "/");
		temp = ft_strjoin(aux, argv);
		if (access(temp, F_OK) == 0)
		{
			str = ft_substr(temp, 0, ft_strlen(temp));
			free(temp);
			free(aux);
			free_matrix(paths_aux);
			return (str);
		}
		paths++;
		free(temp);
		free(aux);
	}
	free_matrix(paths_aux);
	return (NULL);
}
