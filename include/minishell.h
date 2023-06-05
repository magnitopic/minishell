/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:59:12 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/05 17:28:46 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <errno.h>
#include <string.h>

enum e_quotes{
	NONE,
	SINGLES,
	DOUBLE
};

extern char	*g_prompt;

/* Functions */
void	signal_handler(int sig);
void	execution(char *input, char **comms, char **env);
char	**create_arrays(char **comms, char *name);
char	*create_vars(char *origin, char **env);
void	parsing(char *input, char **paths, char **env);
void	exit_program(char *message);

#endif
