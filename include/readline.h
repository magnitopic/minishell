/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:43:03 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/02 11:56:18 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

/* Defines for prompt colours */
# define PROMPT1 "\033[0;32mMiniShell\033[0m:\033[0;34m"
# define PROMPT2 "$\033[0m "

/* Replace_line shenanigans */
void			rl_replace_line(const char *text, int clear_undo);

#endif
