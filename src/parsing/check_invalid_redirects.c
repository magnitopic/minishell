/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_invalid_redirects.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:23:42 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/15 16:30:02 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	checks(char *str, enum e_redirect *flag, int n)
{
	if (str[n] == '<')
	{
		if (*flag == NO)
			*flag = INPUT;
		else if (*flag == INPUT && str[n - 1] == '<')
			*flag = HEREDOC;
		else
			return (1);
	}
	else if (str[n] == '>')
	{
		if (*flag == 5)
			*flag = 1;
		else if (*flag == OUTPUT && str[n - 1] == '>')
			*flag = APPEND;
		else
			return (1);
	}
	if (str[n] == '|' && *flag != NO)
		return (1);
	if (str[n] != '>' && str[n] != '<' && str[n] != ' '
		&& str[n] != '|')
		*flag = NO;
	return (0);
}

int	check_invalid_redirects(char *str)
{
	enum e_redirect	flag;
	int				n;

	n = 0;
	flag = NO;
	while (str[n])
	{
		if (check_flag(str, n) == NONE)
		{
			if ((str[n] == '<' || str[n] == '>') && !str[n + 1])
				return (0);
			if (checks(str, &flag, n))
				return (0);
		}
		if (check_flag(str, n) != NONE)
			flag = NO;
		n++;
	}
	return (1);
}
