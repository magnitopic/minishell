/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:43:03 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/28 15:01:45 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

/* Defines for prompt colours */
# define PROMPT1 "\001\033[0;32m\002MiniShell\001\033[0m\002:\001\033[0;34m\002"
# define PROMPT2 "\001\033[0m\002$ "
# define HEREDOC_PROMPT1 "\033[0;34m→ heredoc\033[0m:\033[0;33m"
# define HEREDOC_PROMPT2 "\033[0m$ "

/* Replace_line shenanigans */
void			rl_replace_line(const char *text, int clear_undo);

#endif
