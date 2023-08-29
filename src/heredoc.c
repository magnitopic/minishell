/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:22:26 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/29 16:02:17 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Deletes all heredoc temp files
*/
void	there_doc(void)
{
	char	*file_name;
	int		i;
	char	*nbr;

	i = 0;
	while (i < 100000)
	{
		nbr = ft_itoa(i);
		file_name = ft_strjoin("/tmp/.heredoc_", nbr);
		free(nbr);
		if (!access(file_name, F_OK))
			unlink(file_name);
		else
			i = -2;
		free(file_name);
		i++;
		if (i == -1)
			break ;
	}
}

/**
 * Creates the temp files that heredoc needs to function. /tmp/.heredoc_*
*/
static char	*create_file(char *str)
{
	char	*file_name;
	int		fd;
	int		i;
	char	*nbr;

	i = 0;
	while (i < 100000)
	{
		nbr = ft_itoa(i);
		file_name = ft_strjoin("/tmp/.heredoc_", nbr);
		free(nbr);
		if (access(file_name, F_OK))
			break ;
		free(file_name);
		i++;
	}
	fd = open(file_name, O_CREAT | O_RDWR, 0644);
	write(fd, str, ft_strlen(str));
	close(fd);
	return (file_name);
}

static char	*exec_heredoc(char *key_word)
{
	char	*input;
	char	*str;
	char	*aux;
	char	*prompt;

	str = ft_calloc(1, 1);
	prompt = get_heredoc_prompt(key_word);
	while (1)
	{
		input = readline(prompt);
		if (input == NULL || ft_strcmp(input, key_word) == 0)
			break ;
		aux = ft_strjoin(str, input);
		free(str);
		str = ft_strjoin(aux, "\n");
		(free(aux), free(input));
	}
	aux = str;
	str = create_file(str);
	free(prompt);
	free(input);
	free(aux);
	return (str);
}

char	*heredoc(char *key_word)
{
	char	*str;
	pid_t	id;
	int		pipefd[2];

	pipe(pipefd);
	id = fork();
	if (id == 0)
	{
		close(pipefd[0]);
		signal(SIGINT, SIG_DFL);
		str = exec_heredoc(key_word);
		ft_putstr_fd(str, pipefd[1]);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	close(pipefd[1]);
	signal(SIGINT, SIG_IGN);
	wait(NULL);
	str = get_next_line(pipefd[0]);
	close(pipefd[0]);
	signal(SIGINT, signal_handler);
	if (str == NULL)
		str = ft_strdup("/dev/null");
	return (str);
}
