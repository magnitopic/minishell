/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:36:37 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/04 12:19:50 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/**
 * Global variable struct
 */
typedef struct s_shell
{
	char	*prompt;
	int		exit_stat;
	char	**env;
	char	*pwd;
}	t_shell;

/**
 * General variable struct
*/
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
	char	*home;
	char	*pwd;
	char	*parsed;
	char	*value;
	char	*temp;
	char	*aux;
	char	*str;
	char	*path;
	char	*other_aux;
	char	**arr;
}	t_vars;

/**
 * For parsing. Let's us know if the content had quotes or not
*/
typedef struct s_tokens
{
	char			*content;
	int				flag;
	struct s_tokens	*next;
}	t_tokens;

/**
 * Struct for storing redirects
*/
typedef struct s_redi
{
	void			*content;
	enum e_redirect	type;
	struct s_redi	*next;
}	t_redi;

/**
 * Function to keep track of pipe, redirects, and files in `exec()`
*/
typedef struct s_files
{
	struct s_redi	*write;
	struct s_redi	*read;
	char			**arr;
	char			*command;
	int				*fd;
	int				id[1024];
	int				count;
	t_list			*file_d;
}	t_files;

/**
 * Struct to represent all the elements of a command.
 * comm		The command that should be executed
 * args		A list with all the command's arguments
 * redi		A list with all the command's redirects
*/
typedef struct s_command
{
	char		*comm;
	t_list		*args;
	t_redi		*redi;
}	t_command;

#endif
