/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:36:00 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/03 16:10:35 by alaparic         ###   ########.fr       */
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

static t_tokens	*parse_phrase(t_list **list) // Lista con quotes spliteados
{
	t_list		*aux;
	t_tokens	*tokens;

	aux = *list;
	tokens = NULL;
	while (aux)
	{
		ft_addnew_token(&tokens, split_quotes(aux->content));
		aux = aux->next;
	}
	free_lists(list);
	return (tokens);
}

static char	*join_phrases(t_list *list)
{
	char	*str;
	char	*aux;

	str = list->content;
	while (list->next)
	{
		list = list->next;
		aux = str;
		if (list->content && ft_strtrim(list->content, " 	") != NULL)
			str = ft_strjoin(str, list->content);
		free(aux);
	}
	return (str);
}

t_list	*expand_values(t_list *args)
{
	t_list		*splitted;
	t_list		*aux;
	char		*str_aux;

	aux = args;
	splitted = NULL;
	while (args)
	{
		ft_printf("value: |%s|\n", args->content);
		str_aux = ft_strtrim(args->content, " 	");
		while (!args->content || ft_strlen(str_aux) < 1)
		{
			free(str_aux);
			args = args->next;
			str_aux = ft_strtrim(args->content, " 	");
		}
		quote_split(str_aux, &splitted);
		aux->content = parse_phrase(&splitted);
		aux->content = join_phrases(aux->content);
		(free_lists(&splitted), splitted = NULL);
		args = args->next;
	}
	return (aux);
}