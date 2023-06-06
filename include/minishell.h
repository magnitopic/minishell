/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:59:12 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/06 20:12:21 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <string.h>

/* Defines */
# define PROMPT1 "\033[0;34mMiniShell:\033[0;32m"
# define PROMPT2 "\033[0m$ "

/* Enums */
enum e_quotes
{
	NONE,
	SINGLES,
	DOUBLE
};

/* Structs */
typedef struct s_shell
{
	char	*prompt;
}	t_shell;

/* Global variable */
t_shell	*g_shell;

/* Functions */
void	signal_handler(int sig);
void	execution(char *input, char **comms, char **env);
char	**create_arrays(char **comms, char *name);
char	*create_vars(char *origin, char **env);
void	parsing(char *input, char **paths, char **env);
void	exit_program(char *message);
char	**parse_words(char *str, char **arr);

#endif
