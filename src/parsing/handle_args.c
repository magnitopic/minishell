/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:36:00 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/03 16:55:39 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	quote_split(char *str, t_list **splitted)
{
	char			len;
	int				i;
	enum e_quotes	flag;
	enum e_quotes	old_flag;

	i = 0;
	flag = 0;
	old_flag = check_flag(str, i);
	while (str[i])
	{
		len = 0;
		flag = check_flag(str, i + len);
		while (flag == old_flag && str[i + len])
			flag = check_flag(str, i + ++len);
		if (old_flag != NONE)
			flag = check_flag(str, i + ++len);
		ft_lstadd_new(splitted, ft_substr(str, i, len));
		i = i + len;
		old_flag = flag;
	}
	free(str);
}

static void	parse_phrase(t_list **list, char **env)
{
	t_list			*aux;

	aux = *list;
	while (aux)
	{
		aux->content = split_quotes(aux->content, env);
		aux = aux->next;
	}
}

static char	*join_phrases(t_list	*list)
{
	char	*str;
	char	*aux;

	str = list->content;
	aux = "";
	list = list->next;
	while (list)
	{
		aux = str;
		str = ft_strjoin(str, list->content);
		free(aux);
		list = list->next;
	}
	return (str);
}

char	**expand_values(char **args, char **env)
{
	char	**aux;
	t_list	*splitted;

	aux = args;
	splitted = NULL;
	while (*aux)
	{
		quote_split(ft_strtrim(*aux, " 	"), &splitted);
		parse_phrase(&splitted, env);
		*aux = join_phrases(splitted);
		(free_stacks(&splitted), splitted = NULL);
		aux++;
	}
	return (args);
}
