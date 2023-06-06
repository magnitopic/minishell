/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:58:31 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/06 17:24:51 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*char	*parse_quotes(char *input)
{
	char	*parsed;
	int		i;

	i = 0;
	while(input)
	{

	}
}*/

enum e_quotes	check_flag(char *str, int n, enum e_quotes flag)
{
	if (*(str + n) == 34 && flag == NONE)
		flag = DOUBLE;
	else if (*(str + n) == 39 && flag == NONE)
		flag = SINGLES;
	else if ((flag == SINGLES && *(str + n) == 39)
		|| (flag == DOUBLE && *(str + n) == 34))
		flag = NONE;
	return (flag);
}

int	num_words(char *str)
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
		flag = check_flag(str, n, flag);
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

char	**parse_words(char *str, char **arr)
{
	int				n;
	int				aux;
	int				index;
	int				j;
	enum e_quotes	flag;

	flag = NONE;
	n = 0;
	aux = 0;
	index = 0;
	j = 0;
	arr = ft_calloc(num_words(str) + 1, sizeof(char *));
	while (str[n])
	{
		flag = check_flag(str, n, flag);
		if ((str[n] == ' ' && flag == NONE && index == 0)
			|| (!str[n + 1] && str[n] != ' '))
		{
			arr[j] = ft_substr(str, aux, n - aux);
			aux = n;
			j++;
			index = 1;
		}
		if (str[n] != ' ' || flag != NONE)
			index = 0;
		if (str[n] == ' ' && index == 1)
			aux = n;
		n++;
	}
	return (arr);
}
