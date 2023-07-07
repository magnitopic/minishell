/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:59:12 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/07 12:28:07 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

/* Defines */
# define PROMPT1 "\001\033[0;32m\002MiniShell\001\033[0m\002:\001\033[0;34m\002"
# define PROMPT2 "\001\033[0m\002$ "

/* Enums */
enum e_quotes
{
	NONE,
	SINGLE,
	DOUBLE
};

/* Structs */
typedef struct s_shell
{
	char	*prompt;
}	t_shell;

typedef struct s_vars
{
	int		flag;
	int		in;
	int		end;
	int		n;
	int		len;
	int		st;
	int		i;
	int		index;
	int		j;
	char	*value;
	char	*temp;
	char	*aux;
	char	*str;
	char	*path;
	char	*other_aux;
	char	**arr;
}	t_vars;

typedef struct s_command
{
	char				*comm;
	t_list				*args;
	t_list				*redi;
}	t_command;

/* Global variable */
t_shell	*g_shell;

/* Replace line shenanigans */
void			rl_replace_line(const char *text, int clear_undo);

/* Functions */
t_list			*expand_values(t_list *args, char **env);
void			set_prompt(void);
void			signal_handler(int sig);
t_list			*split_words(char *str);
int				check_unclosed_quotes(char *input);
void			free_stacks(t_list **list);
void			exit_program(char *message);
char			*expand_vars(char *var, char **env);
char			*create_vars(char *origin, char **env);
char			**create_arrays(char **comms, char *name);
void			parsing(char *input, char **paths, char **env);
enum e_quotes	check_flag(char *str, int n);
void			execution(t_command *input, char **paths, char **env);
char			*split_quotes(char *input, char **env);
char			*add_values(char *command, char **env);
t_list			*find_name_vars(char *var);
char			*get_var_value(char *name, char **env);
void			free_commands(t_list *input);
/* BuiltIn Functions */
void			bi_echo(t_command *com);
void			bi_exit(t_command *com);

#endif
