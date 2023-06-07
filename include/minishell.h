/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:59:12 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/07 16:22:41 by alaparic         ###   ########.fr       */
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
# define PROMPT1 "\033[0;32mMiniShell\033[0m:\033[0;34m"
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
void			set_prompt(void);
void			signal_handler(int sig);
char			**create_arrays(char **comms, char *name);
char			*create_vars(char *origin, char **env);
void			parsing(char *input, char **paths, char **env);
void			exit_program(char *message);
char			**parse_words(char *str, char **arr);
void			free_stacks(t_list **list);
char			*parse_quotes(char *input);
void			execution(char *input, char **comms, char **env);
enum e_quotes	check_flag(char *str, int n, enum e_quotes flag);
char			*expand_var(char *var, char **env);

#endif
