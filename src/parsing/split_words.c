/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:58:31 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/15 13:44:24 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*add_to_list(t_list *list, char *str, int pos, int last_pos)
{	
	while (str[pos] != '\0')
	{
		if ((str[pos] == '>' || str[pos] == '<') && !check_flag(str, pos))
		{
			if (pos > 0 && str[pos - 1] != ' ')
				ft_lstadd_new(&list, ft_substr(str, last_pos, pos - last_pos));
			last_pos = pos;
			while (((str[pos] == '>' || str[pos] == '<')
					&& !check_flag(str, pos)) && str[pos + 1])
				pos++;
			ft_lstadd_new(&list, ft_substr(str, last_pos, pos - last_pos));
			last_pos = pos;
		}
		while ((str[pos + 1] == ' ' && !check_flag(str, pos + 1)))
			pos++;
		if ((str[pos] == ' ' && !check_flag(str, pos)) || !str[pos + 1])
		{
			ft_lstadd_new(&list, ft_substr(str, last_pos, pos + 1 - last_pos));
			last_pos = pos + 1;
		}
		pos++;
	}
	return (list);
}

t_list	*split_words(char *str)
{
	t_list	*list;
	int		pos;
	int		last_pos;

	pos = 0;
	last_pos = 0;
	list = NULL;
	list = add_to_list(list, str, pos, last_pos);
	(free(str), str = NULL);
	return (list);
}
