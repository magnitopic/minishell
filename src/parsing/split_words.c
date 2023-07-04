/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:58:31 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/04 12:28:33 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Counts the number of words for `split_words`
 */
/* static int	num_words(char *str)
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
} */

// TODO: Hacer una función que nos separe los redirects y ver si es posible
// hacer mediante strrchr o cuál es la manera más eficiente

/* char	**diputado(char **arr)
{
	char	**new_str;

	while (*arr)
	{
		
		arr++;
	}
} */

/**
 * Receives a command as in input. It separates the different words
 * of the command. The command itself and it's parameters.
*/
/* char	**split_words(char *str)
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
	return (diputado(a.arr));
} */

static void	split_redirects(char *str, int pos, int last_pos, t_list **list)
{
	pos++;
	while (str[pos] != '>' && str[pos] != '<' && str[pos] != ' '
		&& str[pos] != '\0')
		pos++;
	//printf("SPLIT: %s\n", ft_substr(str, last_pos, pos - last_pos));
	ft_lstadd_new(list, ft_substr(str, last_pos, pos - last_pos));
	last_pos = pos;
}

t_list	*split_words(char *str)
{
	t_list	*list;
	int		pos;
	int		last_pos;

	pos = 0;
	last_pos = 0;
	list = NULL;
	while (str[pos] != '\0')
	{
		while ((str[pos + 1] == ' ' && !check_flag(str, pos + 1)))
			pos++;
		if ((str[pos] == ' ' && !check_flag(str, pos)) || !str[pos + 1])
		{
			//printf("SPLIT: %s\n", ft_substr(str, last_pos, pos + 1 - last_pos));
			ft_lstadd_new(&list, ft_substr(str, last_pos, pos + 1 - last_pos));
			last_pos = pos + 1;
		}
		else if ((str[pos] == '>' || str[pos] == '<') && !check_flag(str, pos))
			split_redirects(str, pos, last_pos, &list);
		pos++;
	}
	return (list);
}
