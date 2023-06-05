/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:35:44 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/05 12:30:55 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*g_prompt;

char	**put_path(char **paths, char **env)
{
	char	*line;
	int		y;

	y = 0;
	while (env[y] != NULL && ft_strncmp("PATH=", env[y], 5) != 0)
		y++;
	line = ft_calloc(ft_strlen(env[y]) - 4, sizeof(char));
	if (!line)
	{
		perror("malloc");
		exit (EXIT_FAILURE);
	}
	ft_strlcpy(line, env[y] + 5, ft_strlen(env[y]) - 4);
	paths = ft_split(line, ':');
	if (!paths)
		(perror("split"), exit (EXIT_FAILURE));
	free(line);
	return (paths);
}

void	ft_leaks(void)
{
	system("Leaks minishell");
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	**paths;
	char	path[PATH_MAX];

	atexit(ft_leaks);
	if (!env[0])
	{
		perror("environment");
		exit(EXIT_FAILURE);
	}
	((void)argv, (void)argc);
	paths = NULL;
	paths = put_path(paths, env);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	g_prompt = ft_strjoin("\033[0;34mMiniShell\033[0m:\033[0;32m", \
	ft_strjoin(getcwd(path, sizeof(path)), "\033[0m$ "));
	while (1)
	{
		input = readline(g_prompt);
		if (input == 0)
			exit_program("\nexit\n");
		if (ft_strlen(ft_strtrim(input, " \n\t\r\v\f")) != 0)
		{
			add_history(ft_strtrim(input, " \n\t\r\v\f"));
			parsing(input, paths, env);
		}
		free(input);
	}
	free_matrix(paths);
	return (0);
}
