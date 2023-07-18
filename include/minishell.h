/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:59:12 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/18 12:36:19 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <limits.h>
# include <signal.h>
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

/**
 * INPUT		<
 * OUTPUT		>
 * HEREDOC		<<
 * APPEND		>>
 * BAD_INPUT	something different
 */
enum e_redirect
{
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
	BAD_INPUT
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

typedef struct s_redi
{
	void			*content;
	enum e_redirect	type;
	struct s_redi	*next;
}	t_redi;

typedef struct s_files
{
	struct s_redi	*write;
	struct s_redi	*read;
	char			**arr;
	char			*command;
	int				*fd;
	int				id;
}	t_files;

typedef struct s_command
{
	char		*comm;
	t_list		*args;
	t_redi		*redi;
}	t_command;

/* Global variable */
t_shell	*g_shell;

/* Replace line shenanigans */
void			rl_replace_line(const char *text, int clear_undo);

/* Functions */

void			set_prompt(void);
void			signal_handler(int sig);
void			free_stacks(t_list **list);
void			exit_program(char *message);
void			ft_perror(char *message);
char			*expand_vars(char *var, char **env);
char			*create_vars(char *origin, char **env);
char			**create_arrays(char **comms, char *name);
void			print_commands(t_command *input, char **paths, char **env);
void			free_commands(t_list *input);
char			*heredoc(char *key_word);
void			ft_newcommand(t_redi **list, void *cont, enum e_redirect type);
char			**set_for_execve(t_files *files, t_command *input);
/* Execution */
void			exec(t_list *com, t_files *files, char **paths, char **env);
/* Parsing functions */
t_list			*split_words(char *str);
enum e_quotes	check_flag(char *str, int n);
int				check_unclosed_quotes(char *input);
char			*get_var_value(char *name, char **env);
char			*add_values(char *command, char **env);
char			*split_quotes(char *input, char **env);
t_list			*expand_values(t_list *args, char **env);
void			parsing(char *input, char **paths, char **env);
int				handle_redirects(char *str, t_redi **redi, t_list **tokens);
/* BuiltIn Functions */
void			bi_echo(t_command *com);
void			bi_exit(t_command *com);
void			bi_pwd(t_command *com);
void			bi_cd(t_command *com, char **env);
void			bi_env(t_command *com, char **env);
void			bi_export(t_command *input, char **env);
void			bi_unset(t_command *input, char **env);

#endif
