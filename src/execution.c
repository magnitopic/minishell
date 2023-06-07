/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:27:28 by jsarabia          #+#    #+#             */
/*   Updated: 2023/06/07 11:33:25 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	change_dir(char **arr, char **env)
{
	char	*pwd;
	char	*buf;
	char	*home;
	int		len;
	char	path[PATH_MAX];

	buf = NULL;
	pwd = NULL;
	home = create_vars("HOME", env);
	if (!arr[1])
	{
		chdir(home);
		free(home);
		return ;
	}
	if (access(arr[1], F_OK) == 0)
	{
		chdir(arr[1]);
		return ;
	}
	buf = getcwd(path, sizeof(path));
	if (ft_strncmp(arr[1], "..", 2) == 0)
	{
		len = ft_strlen(ft_strrchr(buf, '/'));
		pwd = ft_substr(buf, 0, ft_strlen(buf) - len);
		chdir(pwd);
		free(pwd);
		if (ft_strlen(arr[1]) == 2)
			return ;
	}
	if (!pwd)
	{
		pwd = ft_strjoin(buf, "/");
		buf = ft_strjoin(pwd, arr[1]);
		if (access(buf, F_OK) == 0)
		{
			chdir(buf);
			free(pwd);
			free(buf);
		}
		else
			perror("cd");
	}
}

static char	*check_param(char *argv)
{
	char	*str;
	char	**aux;

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

static char	*find_command(char *argv, char **paths)
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

static void	execute_one(char **comms, char **paths, char **env)
{
	char	**arr;
	char	*name;
	int		id;

	// TODO: Check for built-in commands
	name = find_command(comms[0], paths);
	if (!name)
	{
		perror("command");
		return ;
	}
	arr = create_arrays(comms, name);
	if (ft_strncmp(comms[0], "cd", 2) == 0)
		return (change_dir(arr, env));
	id = fork();
	if (id == 0)
	{
		execve(name, arr, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(id, NULL, 0);
	free_matrix(arr);
	free(name);
}

void	execution(char *input, char **paths, char **env)
{
	char	**comms;

	if ((!ft_strncmp(input, "exit", ft_strlen(input))
			|| !(ft_strncmp(input, "exit ", 5))) && input[0] != 0)
		exit_program("exit\n");
	comms = ft_split(input, '|');
	if (!comms[1])
		execute_one(comms, paths, env);
	free_matrix(comms);
}
