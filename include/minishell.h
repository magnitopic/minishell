/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:59:12 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/29 15:39:51 by alaparic         ###   ########.fr       */
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

void			there_doc(void);
char			*set_prompt(void);
char			**cpy_env(char **env);
char			*expand_vars(char *var);
void			signal_handler(int sig);
void			ft_perror(char *message);
void			free_redi(t_redi **redi);
char			*heredoc(char *key_word);
void			free_lists(t_list **list);
char			*create_vars(char *origin);
void			free_stacks(t_list **list);
void			free_files(t_files **file);
void			exit_program(int err_code);
void			free_commands(t_list **cmd);
void			free_tokens(t_tokens **list);
int				check_invalid_redirects(char *str);
char			*get_heredoc_prompt(char *key_word);
char			**create_arrays(char **comms, char *name);
char			**set_for_execve(t_files *files, t_command *input);
void			ft_newcommand(t_redi **list, void *cont, enum e_redirect type);

/* Execution */

char			**get_path(void);
char			*check_param(char *argv);
char			*find_command(char *argv);
int				check_builtin_str(char *str);
int				check_builtin(t_command *input);
void			exec(t_list *com, t_files *files);
int				check_path(char *str, char **paths);
t_files			*create_files(t_command *input, t_files *files);
t_files			*check_files(t_files *files, char *name, int flag);
int				exec_cmd(t_command *input, t_files *files, int flag);
t_files			*execute_first(t_command *input, t_files *files, t_list *com);
t_files			*execute_final(t_command *input, t_files *files, t_list *com);
int				exec_child(t_command *in, t_files *fil, t_list *com, int *fd);
t_files			*execute_pipes(t_command *in, t_files *fil, int i, t_list *com);
char			*find_name_com(char **paths, char **paux, char *au, char *argv);
int				read_infile(t_redi *read, int num, t_files *files, t_list *com);
void			exec_one_builtin(t_command *input, t_files *files, t_list *com);
int				write_outfile(t_redi *wr, int num, t_files *files, t_list *com);

/* Parsing functions */

void			parsing(char *input);
t_list			*split_words(char *str);
int				check_empty(t_list *args);
char			*add_values(char *command);
char			*get_var_value(char *name);
char			*split_quotes(char *input);
t_tokens		*list_to_token(t_list *lst);
enum e_quotes	check_flag(char *str, int n);
int				check_redis(t_list *commands);
t_tokens		*expand_values(t_list *old_args);
t_tokens		*ft_token_new(char *str, int flag);
int				check_unclosed_quotes(char *input);
int				find_dollar_pos(char *str, int pos);
void			ft_lstadd_token(t_tokens **token, char *str);
void			ft_addnew_token(t_tokens **tokens, t_tokens *token);
int				handle_redirects(char *str, t_redi **redi, t_tokens **tokens);

/* BuiltIn Functions */

void			bi_exit(t_command *com, int num);
void			bi_pwd(t_command *com, int num);
void			bi_cd(t_command *com, int num);
void			bi_env(t_command *com, int num);
void			print_export(char **env);
int				invalid_value(char **env);
char			*get_value_for_var(char *str);
void			bi_echo(t_command *com, int flag);
void			bi_unset(t_command *input, int num);
void			bi_export(t_command *input, int num);

#endif
