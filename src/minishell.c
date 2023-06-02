/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:35:44 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/01 18:12:50 by alaparic         ###   ########.fr       */
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
	{
		perror("split");
		exit (EXIT_FAILURE);
	}
	free(line);
	return (paths);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	**paths;
	char	path[PATH_MAX];

	((void)argv, (void)argc);
	if (!env)
	{
		perror("environment");
		exit(EXIT_FAILURE);
	}
	paths = NULL;
	paths = put_path(paths, env);
	signal(SIGINT, signal_handler);
	g_prompt = ft_strjoin("\033[0;34mMiniShell\033[0m:\033[0;32m", \
	ft_strjoin(getcwd(path, sizeof(path)), "\033[0m$ "));
	while (1)
	{
		input = readline(g_prompt);
		if (ft_strlen(ft_strtrim(input, " \n\t\r\v\f")) != 0)
		{
			add_history(ft_strtrim(input, " \n\t\r\v\f"));
			execution(input, paths, env);
		}
	}
	return (0);
}
