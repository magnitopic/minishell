/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:27:48 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/02 15:43:36 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**set_for_execve(t_files *files, t_command *input)
{
	char	**com_args;
	t_list	*aux;
	int		len;
	int		i;

	aux = input->args;
	len = ft_lstsize(aux);
	com_args = ft_calloc(len + 2, sizeof(char *));
	com_args[0] = files->command;
	i = 1;
	while (aux)
	{
		com_args[i] = aux->content;
		aux = aux->next;
		i++;
	}
	return (com_args);
}

t_files	*handle_file(char *name, int flag, t_files *files)
{
	if (flag == 1 || flag == 3)
	{
		/*if (flag == 1)
			unlink(name);*/
		if (access(name, F_OK))
			open(name, O_CREAT, 0644);
		files->write->content = ft_substr(name, 0, ft_strlen(name));
		files->write->type = flag;
	}
	else if (flag == 0 || flag == 2)
	{
		files->read->content = ft_substr(name, 0, ft_strlen(name));
		files->read->type = flag;
	}
	return (files);
}

t_files	*create_files(t_command *input, t_files *files)
{
	char	*filename;

	while (input->redi)
	{
		filename = input->redi->content;
		files = handle_file(filename, input->redi->type, files);
		if (files == NULL)
			return (NULL);
		if (input->redi->next)
			input->redi = input->redi->next;
		else
			break ;
	}
	return (files);
}

char	*check_param(char *argv)
{
	char	*str;
	char	**aux;

	if (!argv)
		argv = ft_substr("echo", 0, 4);
	aux = ft_split(argv, ' ');
	if (!aux)
	{
		str = ft_substr(argv, 0, ft_strlen(argv));
		free_matrix(aux);
		return (str);
	}
	str = ft_substr(aux[0], 0, ft_strlen(aux[0]));
	free_matrix(aux);
	return (str);
}

char	*find_command(char *argv, char **paths)
{
	char	*str;
	char	*temp;
	char	*aux;

	argv = check_param(argv);
	if (access(argv, F_OK) == 0 && !check_builtin_str(argv) && !check_path(argv, paths))
	{
		ft_printf("ey: %s\n", argv);
		return (argv);
	}
	while (*paths != NULL)
	{
		aux = ft_strjoin(*paths, "/");
		temp = ft_strjoin(aux, argv);
		if (access(temp, F_OK) == 0)
		{
			str = ft_substr(temp, 0, ft_strlen(temp));
			free(temp);
			free(aux);
			free(argv);
			return (str);
		}
		paths++;
		free(temp);
		free(aux);
	}
	free(argv);
	return (NULL);
}
