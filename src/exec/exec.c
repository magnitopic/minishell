/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:27:28 by jsarabia          #+#    #+#             */
/*   Updated: 2023/07/12 19:13:23 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* static void	change_dir(char **arr, char **env)
{
	char	*pwd;
	char	*buf;
	char	*home;
	int		len;
	char	path[PATH_MAX];

	buf = NULL;
	pwd = NULL;
	if (!arr[1])
	{
		home = create_vars("HOME", env);
		chdir(home);
		free(home);
		free(arr);
		return ;
	}
	if (access(arr[1], F_OK) == 0)
	{
		chdir(arr[1]);
		free(arr);
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
	free(arr);
	free(pwd);
	free(buf);
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
	{
		free(name);
		return (change_dir(arr, env));
	}
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
} */

t_files	*handle_file(char *name, int flag, t_files *files)
{
	if (flag == 1 || flag == 3)
	{
		ft_printf("One!\n");
		if (flag == 1)
			unlink(name);
		open(name, O_CREAT, 0644);
		files->write->content = ft_substr(name, 0, ft_strlen(name));
		files->write->type = flag;
	}
	else if (flag == 0 || flag == 2)
	{
		if (flag == 0 && access(name, R_OK) != 0)
			exit(EXIT_FAILURE);			// TODO: hacer que esto funcione bien
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
		if (input->redi->next)
			input->redi = input->redi->next;
		else
			break ;
	}
	return (files);
}

/* void	print_commands(t_command *input, char **paths, char **env)
{
	t_redi	*aux;
	t_list	*aux_two;

	aux = input->redi;
	aux_two = input->args;
	((void)paths, (void)env);
	if (input->comm)
	{
		printf("command: %s\n", input->comm);
		//execute_one(&input->comm, paths, env);
	}
	while (aux)
	{
		printf("redi: %s\n", (char *)aux->content);
		printf("  -> type: %d\n", (int)aux->type);
		aux = aux->next;
	}
	while (aux_two)
	{
		printf("args: %s\n", (char *)aux_two->content);
		aux_two = aux_two->next;
	}
} */

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

int	*read_infile(t_redi *read)
{
	int	*fd;

	fd = ft_calloc(3, sizeof(int));
	fd[0] = open(read->content, O_RDONLY);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (fd);
}

void	execute_final(t_command *input, char **paths, char **env)
{
	t_files	*files;

	files = ft_calloc(1, sizeof(t_files));
	files->write = ft_calloc(1, sizeof(t_redi));
	files->read = ft_calloc(1, sizeof(t_redi));
	((void)paths, (void)env);
	if (input->redi && input->redi->type != 4)
		files = create_files(input, files);
	files->command = find_command(input->comm, paths);
	files->arr = set_for_execve(files, input);
	if (files->read)
		files->fd = read_infile(files->read);
	files->id = fork();
	if (files->id == 0)
	{
		if (files->write)
		{
			files->fd[1] = open(files->write->content, O_WRONLY);
			dup2(files->fd[1], 1);
			close(files->fd[1]);
		}
		execve(files->command, files->arr, env);
	}
	waitpid(files->id, NULL, 0);
}




/*
void	exec_redis(t_redi *redis)
{
	while (redis)
	{

	}

}

void	execution(t_command *com, char **paths, char **env)
{
	((void)paths, (void)env);
	exec_redis(com->redi);
	//exec_cmd();
	//pipes();
}
*/
