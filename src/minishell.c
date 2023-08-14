/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:35:44 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/14 18:13:22 by alaparic         ###   ########.fr       */
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
		exit_program(EXIT_SUCCESS);
	if (ft_strlen(input) != 0)
	{
		add_history(input);
		parsing(input);
	}
	free(input);
	free(g_shell->prompt);
}

int	main(int argc, char **argv, char **env)
{
	int		input;
	int		output;
	char	path[PATH_MAX];

	((void)argv, (void)argc);
	input = dup(STDIN_FILENO);
	output = dup(STDOUT_FILENO);
	g_shell = malloc(sizeof(t_shell));
	g_shell->env = cpy_env(env);
	g_shell->pwd = ft_strdup(getcwd(path, sizeof(path)));
	g_shell->exit_stat = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		user_input(input, output);
	close(input);
	close(output);
	return (0);
}
