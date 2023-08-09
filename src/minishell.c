/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:35:44 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/09 16:16:16 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * This function will be called all throughout the lifetime of the program.
 * It will set the prompt, read the user's input and call the rest of the
 * program's functions.
*/
static void	user_input(int in, int out)
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
		parsing(input);
	}
	free(input);
	free(g_shell->prompt);
}

void	ft_leaks(void)
{
	system("Leaks minishell");
}

int	main(int argc, char **argv, char **env)
{
	int		input;
	int		output;
	char	path[PATH_MAX];

	//atexit(ft_leaks);
	((void)argv, (void)argc);
	input = dup(STDIN_FILENO);
	output = dup(STDOUT_FILENO);
	g_shell = malloc(sizeof(t_shell));
	g_shell->env = cpy_env(env);
	g_shell->pwd = ft_strdup(getcwd(path, sizeof(path)));
	g_shell->exit_stat = 0;
	if (!g_shell->env[0])
	{
		ft_putstr_fd("\033[0;31mError: No environment provided\033[0;\n", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		user_input(input, output);
	close(input);
	close(output);
	return (0);
}
