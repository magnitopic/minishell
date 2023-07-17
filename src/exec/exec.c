/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:27:28 by jsarabia          #+#    #+#             */
/*   Updated: 2023/07/17 11:58:11 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_files	*handle_file(char *name, int flag, t_files *files)
{
	if (flag == 1 || flag == 3)
	{
		if (flag == 1)
			unlink(name);
		open(name, O_CREAT, 0644);
		files->write->content = ft_substr(name, 0, ft_strlen(name));
		files->write->type = flag;
	}
	else if (flag == 0 || flag == 2)
	{
		if (flag == 0 && access(name, R_OK) != 0)
			exit_program("Unable to read file\n");			// TODO: hacer que esto funcione bien
		files->read->content = ft_substr(name, 0, ft_strlen(name));
		files->read->type = flag;
	}
	return (files);
}

static t_files	*create_files(t_command *input, t_files *files)
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

static int	*read_infile(t_redi *read)
{
	int	*fd;

	fd = ft_calloc(3, sizeof(int));
	fd[0] = open(read->content, O_RDONLY);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (fd);
}

static void	exec_cmd(t_command *input, t_files *files, char **env)
{
	int	len;

	len = ft_strlen(input->comm);
	if (ft_strncmp(input->comm, "cd", len) == 0)
		bi_cd(input, env);
	else if (ft_strncmp(input->comm, "echo", len) == 0)
		bi_echo(input);
	else if (ft_strncmp(input->comm, "env", len) == 0)
		bi_env(input, env);
	else if (ft_strncmp(input->comm, "exit", len) == 0)
		bi_exit(input);
	else if (ft_strncmp(input->comm, "export", len) == 0)
		bi_export(input, env);
	else if (ft_strncmp(input->comm, "pwd", len) == 0)
		bi_pwd(input);
	else if (ft_strncmp(input->comm, "unset", len) == 0)
		bi_unset(input, env);
	else
		execve(files->command, files->arr, env);
}

int	*execute_final(t_command *input, char **paths, char **env, t_files *files)
{
	if (files->fd[0] != 0)
	{
		dup2(files->fd[0], STDIN_FILENO);
		close(files->fd[0]);
	}
	files->write = ft_calloc(1, sizeof(t_redi));
	files->read = ft_calloc(1, sizeof(t_redi));
	((void)paths, (void)env);
	if (input->redi && input->redi->type != 4)
		files = create_files(input, files);
	files->command = find_command(input->comm, paths);
	files->arr = set_for_execve(files, input);
	if (files->read->content)
		files->fd = read_infile(files->read);
	if (files->write->content)
	{
		files->fd[1] = open(files->write->content, O_WRONLY);
		dup2(files->fd[1], 1);
		close(files->fd[1]);
	}
	execve(files->command, files->arr, env);
	close(files->fd[0]);
	close(files->fd[1]);
	return (files->fd);
}

int	*execute_pipe(t_command *input, char **paths, char **env, t_files *files)
{
	int	*fd;

	fd = ft_calloc(3, sizeof(int));
	if (files->fd[0] != 0)
	{
		dup2(files->fd[0], STDIN_FILENO);
		close(files->fd[0]);
	}
	files->write = ft_calloc(1, sizeof(t_redi));
	files->read = ft_calloc(1, sizeof(t_redi));
	((void)paths, (void)env);
	if (input->redi && input->redi->type != 4)
		files = create_files(input, files);
	files->command = find_command(input->comm, paths);
	printf("command: %s\n", files->command);
	printf("YES");
	files->arr = set_for_execve(files, input);
	if (files->read->content)
		files->fd = read_infile(files->read);
	pipe(fd);
	files->id = fork();
	if (files->id == 0)
	{
		if (files->write->content)
		{
			fd[1] = open(files->write->content, O_WRONLY);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		else
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			close(fd[0]);
			close(files->fd[0]);
			close(files->fd[1]);
		}
		exec_cmd(input, files, env);
	}
	waitpid(files->id, NULL, 0);
	free(files->fd);
	return (fd);
}

void	exec(t_list *com, t_files *files, char **paths, char **env)
{
	t_list	*aux;

	aux = com;
	while (com)
	{
		//print_commands(commands->content, paths, env);
		if (!com->next)
			files->fd = execute_final(com->content, paths, env, files);
		else
			files->fd = execute_pipe(com->content, paths, env, files);
		close (files->fd[1]);
		com = com->next;
	}
	free_commands(aux);
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
