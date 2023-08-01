/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:35:44 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/01 19:31:16 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**put_path(char **paths)
{
	char	*line;
	int		y;
	char	**env;

	y = 0;
	env = g_shell->env;
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

static void	user_input(char **paths, int in, int out)
{
	char	*input;
	char	*aux;

	set_prompt();
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	input = readline(g_shell->prompt);
	aux = input;
	input = ft_strtrim(input, " \n\t\r\v\f");
	free(aux);
	if (input == 0)
		exit_program("exit\n");
	if (ft_strlen(input) != 0)
	{
		add_history(input);
		parsing(input, paths);
	}
	free(input);
	free(g_shell->prompt);
}

int	main(int argc, char **argv, char **env)
{
	char	**paths;
	int		input;
	int		output;

	((void)argv, (void)argc);
	input = dup(STDIN_FILENO);
	output = dup(STDOUT_FILENO);
	g_shell = malloc(sizeof(t_shell));
	g_shell->env = cpy_env(env);
	g_shell->exit_stat = 0;
	if (!g_shell->env[0])
	{
		ft_putstr_fd("\033[0;31mError: No environment provided\033[0;\n", 2);
		exit(EXIT_FAILURE);
	}
	paths = put_path(NULL);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		user_input(paths, input, output);
	close(input);
	close(output);
	free_matrix(paths);
	return (0);
}
