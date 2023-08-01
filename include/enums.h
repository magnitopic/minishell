/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:41:01 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/01 19:41:41 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

/**
 * Let's us know what type of quotes we are currently in
*/
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
	BAD_INPUT,
	NO
};

/**
 * INVALID		syntax error
 * NEW_VALUE	adds value to env or replaces existing value
 * CREATE		it creates variable. If it exists it's not modified
*/
enum e_export
{
	INVALID,
	NEW_VALUE,
	CREATE
};

#endif
