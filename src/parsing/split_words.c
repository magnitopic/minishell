/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:58:31 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/05 16:59:26 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		if ((str[pos] == '>' || str[pos] == '<') && !check_flag(str, pos))
		{
			printf("SPLIT: %s\n", ft_substr(str, last_pos, pos - last_pos));
			if (pos > 0 && str[pos - 1] != ' ')
				ft_lstadd_new(&list, ft_substr(str, last_pos, pos - last_pos));
			last_pos = pos;
			while (((str[pos] == '>' || str[pos] == '<')
					&& !check_flag(str, pos)))
				pos++;
			printf("SPLIT: %s\n", ft_substr(str, last_pos, pos - last_pos));
			ft_lstadd_new(&list, ft_substr(str, last_pos, pos - last_pos));
			last_pos = pos;
		}
		if ((str[pos] == ' ' && !check_flag(str, pos)) || !str[pos + 1])
		{
			printf("SPLIT: %s\n", ft_substr(str, last_pos, pos + 1 - last_pos));
			ft_lstadd_new(&list, ft_substr(str, last_pos, pos + 1 - last_pos));
			last_pos = pos + 1;
		}
		pos++;
	}
	return (list);
}
