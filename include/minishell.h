/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:59:12 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/09 15:40:12 by alaparic         ###   ########.fr       */
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
/* Enums */
# include "enums.h"
/* Structs */
# include "structs.h"
/* Readline */
# include "readline.h"

/* Global variable */
t_shell	*g_shell;

/* Functions */

void			set_prompt(void);
char			**cpy_env(char **env);
void			signal_handler(int sig);
void			ft_perror(char *message);
void			free_redi(t_redi **redi);
char			*heredoc(char *key_word);
void			there_doc(void);
void			free_stacks(t_list **list);
void			free_files(t_files *file);
void			free_lists(t_list **list);
void			exit_program(char *message);
void			free_commands(t_list *input);
int				check_invalid_redirects(char *str);
char			*expand_vars(char *var);
char			*create_vars(char *origin);
char			**create_arrays(char **comms, char *name);
char			**set_for_execve(t_files *files, t_command *input);
void			ft_newcommand(t_redi **list, void *cont, enum e_redirect type);
void			free_tokens(t_tokens **list);
/* Execution */
void			exec(t_list *com, t_files *files);
t_files			*handle_file(char *name, int flag, t_files *files, t_list *com);
t_files			*create_files(t_command *input, t_files *files, t_list *com);
char			*check_param(char *argv);
char			*find_command(char *argv);
void			exec_one_builtin(t_command *input, t_files *files, t_list *com);
int				read_infile(t_redi *read, int num, t_files *files, t_list *command);
int				write_outfile(t_redi *write, int num, t_files *files, t_list *command);
int				exec_cmd(t_command *input, t_files *files, int flag);
int				check_builtin(t_command *input);
int				check_builtin_str(char *str);
int				check_path(char *str, char **paths);
char			**get_path(void);
/* Parsing functions */
t_tokens		*list_to_token(t_list *lst);
t_list			*split_words(char *str);
enum e_quotes	check_flag(char *str, int n);
int				check_unclosed_quotes(char *input);
char			*get_var_value(char *name);
int				find_dollar_pos(char *str, int pos);
char			*add_values(char *command);
char			*split_quotes(char *input);
void			ft_lstadd_token(t_tokens **token, char *str);
void			ft_addnew_token(t_tokens **tokens, t_tokens *token);
t_tokens		*ft_token_new(char *str, int flag);
t_tokens		*expand_values(t_list *old_args);
void			parsing(char *input);
int				check_redis(t_list *commands);
int				handle_redirects(char *str, t_redi **redi, t_tokens **tokens);
/* BuiltIn Functions */
void			bi_echo(t_command *com, int flag);
void			bi_exit(t_command *com, int num);
void			bi_pwd(t_command *com, int num);
void			bi_cd(t_command *com, int num);
void			bi_env(t_command *com, int num);
void			bi_export(t_command *input, int num);
void			bi_unset(t_command *input, int num);

#endif
