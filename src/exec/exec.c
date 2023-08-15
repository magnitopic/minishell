/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:27:28 by jsarabia          #+#    #+#             */
/*   Updated: 2023/08/15 15:07:46 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	wait_function(t_files *files)
{
	int		i;
	int		status;
	pid_t	result;

	i = 0;
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		result = waitpid(files->id[i++], &status, 0);
		if (result == -1)
		{
			if (errno == ECHILD)
				break ;
			perror("waitpid");
			break ;
		}
	}
	if (WIFEXITED(status))
		g_shell->exit_stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_shell->exit_stat = WTERMSIG(status) + 128;
	else
		g_shell->exit_stat = 1;
	signal(SIGINT, signal_handler);
}

static void	exec_command_pipes(t_list *com, t_files *files, t_list *aux)
{
	int		i;

	i = 1;
	if ((!com->next && check_builtin(com->content)) || !com->content)
		exec_one_builtin(com->content, files, aux);
	else if (files->count == 1)
		execute_final(com->content, files, aux);
	else if (files->count == 2)
	{
		files = execute_first(com->content, files, aux);
		com = com->next;
		execute_final(com->content, files, aux);
	}
	else if (files->count > 2)
	{
		files = execute_first(com->content, files, aux);
		com = com->next;
		while (com->next)
		{
			files = execute_pipes(com->content, files, i, aux);
			i++;
			com = com->next;
		}
		execute_final(com->content, files, aux);
	}
}

void	exec(t_list *com, t_files *files)
{
	t_list	*aux;

	aux = com;
	files->fd = ft_calloc(2, sizeof(int));
	files->write = ft_calloc(1, sizeof(t_redi));
	files->read = ft_calloc(1, sizeof(t_redi));
	files->count = ft_lstsize(com);
	exec_command_pipes(com, files, aux);
	if (!check_builtin(com->content) || files->count > 1)
		wait_function(files);
	there_doc();
}

/* static void	print_commands(t_command *input)
{
	t_redi	*aux;
	t_list	*aux_two;

	aux = input->redi;
	aux_two = input->args;
	if (input->comm)
	{
		printf("command: %s\n", input->comm);
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
