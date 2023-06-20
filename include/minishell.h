/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:59:12 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/20 18:31:26 by jsarabia         ###   ########.fr       */
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

/* Global variable */
t_shell	*g_shell;

/* Functions */
char			**expand_values(char **args, char **env);
void			set_prompt(void);
void			signal_handler(int sig);
char			**split_words(char *str);
int				check_unclosed_quotes(char *input);
char			*remove_quotes(char *input);
void			free_stacks(t_list **list);
void			exit_program(char *message);
char			*expand_vars(char *var, char **env);
char			*create_vars(char *origin, char **env);
char			**create_arrays(char **comms, char *name);
void			parsing(char *input, char **paths, char **env);
enum e_quotes	check_flag(char *str, int n);
void			execution(char **input, char **paths, char **env);
char			*split_quotes(char *input, char **env);
char			*add_values(char *command, char **env);
t_list			*find_name_vars(char *var);
char			*get_var_value(char *name, char **env);

#endif
