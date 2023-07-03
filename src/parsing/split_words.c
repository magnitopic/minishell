/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:58:31 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/03 16:14:46 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Counts the number of words for `split_words`
 */
static int	num_words(char *str)
{
	int				n;
	int				cont;
	int				index;
	enum e_quotes	flag;

	flag = NONE;
	n = 0;
	cont = 0;
	index = 0;
	while (str[n])
	{
		flag = check_flag(str, n);
		if (str[n] != ' ' || flag != NONE)
			index = 0;
		if ((str[n] == ' ' && flag == NONE && index == 0)
			|| (!str[n + 1] && str[n] != ' '))
		{
			cont++;
			index = 1;
		}
		n++;
	}
	return (cont);
}

/**
 * Receives a command as in input. It separates the different words
 * of the command. The command itself and it's parameters.
*/
char	**split_words(char *str)
{
	t_vars	a;

	a.i = 0;
	a.st = 0;
	a.index = 0;
	a.j = 0;
	a.arr = ft_calloc(num_words(str) + 1, sizeof(char *));
	while (str[a.i])
	{
		if (!str[a.i + 1] && str[a.i] != ' ')
			a.arr[a.j] = ft_substr(str, a.st, a.i - a.st + 1);
		if (str[a.i] == ' ' && check_flag(str, a.i) == NONE && a.index == 0)
		{
			a.arr[a.j] = ft_substr(str, a.st, a.i - a.st);
			a.st = a.i;
			a.j++;
			a.index = 1;
		}
		if (str[a.i] != ' ' || check_flag(str, a.i) != NONE)
			a.index = 0;
		if (str[a.i] == ' ' && a.index == 1)
			a.st = a.i;
		a.i++;
	}
	return (a.arr);
}
