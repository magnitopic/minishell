/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:58:31 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/22 18:20:16 by jsarabia         ###   ########.fr       */
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

static int	count_redirects(char *str)
{
	int	n;
	int	count;
	int	index;

	n = 0;
	count = 0;
	index = -1;
	while (str[n])
	{
		if (str[n] != '<' && str[n] != '>')
		{
			if (index != 0)
				count++;
			index = 0;
		}
		if ((str[n] == '<' || str[n] == '>')
			&& check_flag(str, n) == NONE && index != 1)
		{
			count++;
			index = 1;
		}
		n++;
	}
	return (count);
}

static char	**copy_redirections(char *str, char **arr)
{
	int	j;
	int	n;
	int	in;
	int	count;

	j = 0;
	n = 0;
	in = 0;
	while (arr[j])
		j++;
	count = count_redirects(str);
	while (count > 0)
	{
		if (n != 0)
			in = n;
		while (str[n] == '<' || str[n] == '>' || str[n] == ' ')
			n++;
		if (n != in)
		{
			arr[j] = ft_substr(str, in, n - in);
			j++;
			count--;
		}
		while (str[n] != '<' && str[n] != '>')
			n++;
		if (n != in)
		{
			arr[j] = ft_substr(str, in, n - in);
			j++;
			count--;
		}
	}
	return (arr);
}

char	**split_redirects(char **str)
{
	int		i;
	int		j;
	int		count;
	char	**arr;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((ft_split(str[i], '>') != NULL || ft_split(str[i], '<') != NULL)
			&& ft_strlen(str[i]) != 2)
			j = count_redirects(str[i]);
		if (j == 0 || (j == 1 && (str[i][0] == '<' || str[i][1] == '<'
			|| str[i][0] == '>' || str[i][1] == '>')))
			count += 0;
		else
			count += j;
		printf("%s COUNT: %d\n", str[i], count);
		j = 0;
		i++;
	}
	arr = ft_calloc(count + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (count_redirects(str[i]) == 1)
		{
			arr[j] = ft_substr(str[i], 0, ft_strlen(str[i]));
			printf("STR: %s\n", arr[j]);
			j++;
			i++;
		}
		else
		{
			arr = copy_redirections(str[i], arr);
			j += count_redirects(str[i]) + 1;
			i++;
		}
	}
	free_matrix(str);
	return (arr);
}
