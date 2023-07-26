/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:35:44 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/26 12:29:20 by alaparic         ###   ########.fr       */
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
		ft_perror("malloc");
	ft_strlcpy(line, env[y] + 5, ft_strlen(env[y]) - 4);
	paths = ft_split(line, ':');
	if (!paths)
		ft_perror("split");
	free(line);
	return (paths);
}

static void	user_input(char **paths, char **env, int in, int out)
{
	char	*input;
	char	*aux;

	set_prompt();
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	input = readline(g_sl->prompt);
	aux = input;
	input = ft_strtrim(input, " \n\t\r\v\f");
	free(aux);
	if (input == 0)
		exit_program("exit\n");
	if (ft_strlen(input) != 0)
	{
		add_history(input);
		parsing(input, paths, env);
	}
	free(input);
	free(g_sl->prompt);
}

int	main(int argc, char **argv, char **env)
{
	char	**paths;
	int		input;
	int		output;

	((void)argv, (void)argc);
	input = dup(STDIN_FILENO);
	output = dup(STDOUT_FILENO);
	g_sl = malloc(sizeof(g_sl));
	g_sl->env = cpy_env(env);
	if (!g_sl->env[0])
	{
		ft_putstr_fd("\033[0;31mError: No environment provided\033[0;\n", 2);
		exit(EXIT_FAILURE);
	}
	paths = put_path(NULL, env);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
		user_input(paths, env, input, output);
	close(input);
	close(output);
	free_matrix(paths);
	return (0);
}
