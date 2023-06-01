/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:35:44 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/01 13:16:28 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**put_path(char **paths, char **env)
{
	char	*line;
	int		y;

	y = 0;
	while (env[y] != '\0' && ft_strncmp("PATH=", env[y], 5) != 0)
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

	((void)argv, (void)argc);
	if (!env)
	{
		perror("environment");
		exit(EXIT_FAILURE);
	}
	paths = NULL;
	paths = put_path(paths, env);
	signal(SIGINT, signal_handler);
	while (1)
	{
		input = readline(PROMPT);
		if (ft_strlen(ft_strtrim(input, " \n\t\r\v\f")) != 0)
		{
			add_history(ft_strtrim(input, " \n\t\r\v\f"));
			execution(input, paths, env);
		}
	}
	return (0);
}



