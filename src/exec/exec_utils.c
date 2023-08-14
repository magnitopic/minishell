/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:27:48 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/14 20:13:29 by alaparic         ###   ########.fr       */
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

static t_files	*handle_file(char *name, int flag, t_files *files)
{
	if (flag == 1 || flag == 3)
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
	}
	else if (flag == 0 || flag == 2)
	{
		if (open(name, O_RDONLY) < 0)
		{
			g_shell->exit_stat = 1;
			perror("MiniShell");
			return (NULL);
		}
		if (files->read->content)
			free(files->read->content);
		files->read->content = ft_substr(name, 0, ft_strlen(name));
		files->read->type = flag;
	}
	return (files);
}

t_files	*create_files(t_command *input, t_files *files)
{
	char	*filename;
	t_redi	*aux;

	aux = input->redi;
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
	input->redi = aux;
	return (files);
}

char	**get_paths(void)
{
	char	*line;
	int		y;
	char	**env;
	char	**paths;

	// TODO: Fix leaks
	y = 0;
	env = g_shell->env;
	while (env[y] != NULL && ft_strncmp("PATH=", env[y], 5) != 0)
		y++;
	if (env[y] == NULL)
		return (NULL);
	line = ft_calloc(ft_strlen(env[y]) - 4, sizeof(char));
	if (!line)
		perror("malloc");
	ft_strlcpy(line, env[y] + 5, ft_strlen(env[y]) - 4);
	paths = ft_split(line, ':');
	if (!paths)
		perror("split");
	free(line);
	return (paths);
}

char	*find_command(char *argv)
{
	char	*str;
	char	*temp;
	char	*aux;
	char	**paths_aux;
	char	**paths;

	paths = get_paths();
	paths_aux = paths;
	if (access(argv, F_OK) == 0 && !check_builtin_str(argv)
		&& check_path(argv, paths))
		return (argv);
	if (paths == NULL)
		return (NULL);
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
