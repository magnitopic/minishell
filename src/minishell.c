/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:35:44 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/07 11:56:19 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**put_path(char **paths, char **env)
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

static void	user_input(char **paths, char **env)
{
	char	*input;
	char	*aux;

	set_prompt();
	input = readline(g_shell->prompt);
	aux = input;
	input = ft_strtrim(input, " \n\t\r\v\f");
	free(aux);
	if (input[0] == 0)
		exit_program("\nexit\n");
	if (ft_strlen(input) != 0)
	{
		add_history(input);
		parsing(input, paths, env);
	}
	free(input);
	free(g_shell->prompt);
}

int	main(int argc, char **argv, char **env)
{
	char	**paths;

	atexit(ft_leaks);
	((void)argv, (void)argc);
	g_shell = malloc(sizeof(g_shell));
	if (!env[0])
	{
		perror("environment");
		exit(EXIT_FAILURE);
	}
	paths = put_path(NULL, env);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		user_input(paths, env);
	}
	free_matrix(paths);
	return (0);
}
