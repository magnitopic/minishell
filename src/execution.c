/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:27:28 by jsarabia          #+#    #+#             */
/*   Updated: 2023/06/01 18:16:36 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	change_dir(char **arr)
{
	char	*pwd;
	char	*buf;
	int		len;
	char	path[PATH_MAX];

	buf = NULL;
	pwd = NULL;
	if (!arr[1])
	{
		chdir("~");
		g_prompt = ft_strjoin("\033[0;34mMiniShell\033[0m:\033[0;32m", \
		ft_strjoin(getcwd(path, sizeof(path)), "\033[0m$ "));
		return ;
	}
	if (access(arr[1], F_OK) == 0)
	{
		chdir(arr[1]);
		g_prompt = ft_strjoin("\033[0;34mMiniShell\033[0m:\033[0;32m", \
		ft_strjoin(getcwd(path, sizeof(path)), "\033[0m$ "));
		return ;
	}
	buf = getcwd(path, sizeof(path));
	if (ft_strncmp(arr[1], "..", 2) == 0)
	{
		len = ft_strlen(ft_strrchr(buf, '/'));
		pwd = ft_substr(buf, 0, ft_strlen(buf) - len);
		chdir(pwd);
		if (ft_strlen(arr[1]) == 2)
			return ;
	}
	if (!pwd)
	{
		pwd = ft_strjoin(buf, "/");
		buf = ft_strjoin(pwd, arr[1]);
		if (access(buf, F_OK) == 0)
			chdir(buf);
		else
			perror("cd");
	}
	g_prompt = ft_strjoin("\033[0;34mMiniShell\033[0m:\033[0;32m", \
	ft_strjoin(getcwd(path, sizeof(path)), "\033[0m$ "));
}

char	*check_param(char *argv)
{
	char	*str;
	char	**aux;

	aux = ft_split(argv, ' ');
	if (!aux)
	{
		str = ft_substr(argv, 0, ft_strlen(argv));
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
	if (access(argv, F_OK) == 0)
		return (argv);
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

void	execute_one(char **comms, char **paths, char **env)
{
	char	**arr;
	char	*name;
	int		id;

	name = find_command(comms[0], paths);
	if (!name)
	{
		perror("command");
		return ;
	}
	arr = create_arrays(comms, name);
	if (ft_strncmp(comms[0], "cd", 2) == 0)
		return (change_dir(arr));
	id = fork();
	if (id == 0)
	{
		execve(name, arr, env);
		free_matrix(arr);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(id, NULL, 0);
}

void	execution(char *input, char **paths, char **env)
{
	char	**comms;

	if ((!ft_strncmp(input, "exit", ft_strlen(input))
			|| !(ft_strncmp(input, "exit ", 5))) && input[0] != 0)
		exit(0);
	comms = ft_split(input, '|');
	if (!comms[1])
		execute_one(comms, paths, env);
}
