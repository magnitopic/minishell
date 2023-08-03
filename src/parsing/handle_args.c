/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:36:00 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/03 16:46:32 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	quote_split(char *str, t_tokens **splitted)
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
		ft_lstadd_token(splitted, ft_substr(str, i, len));
		i = i + len;
		old_flag = flag;
	}
	free(str);
}

static void	parse_phrase(t_tokens **list)
{
	t_tokens	*aux;
	char		*str_aux;

	aux = *list;
	while (aux)
	{
		str_aux = aux->content;
		if (ft_strchr(str_aux, '\'') || ft_strchr(str_aux, '"'))
			aux->flag = 1;
		aux->content = split_quotes(aux->content);
		free(str_aux);
		aux = aux->next;
	}
}

static char	*join_phrases(t_tokens *list)
{
	char	*str;
	char	*aux;

	str = ft_strtrim(list->content, " 	");
	while (list->next)
	{
		list = list->next;
		aux = str;
		if (list->content && ft_strtrim(list->content, " 	") != NULL)
			str = ft_strjoin(str, ft_strtrim(list->content, " 	"));
		free(aux);
	}
	return (str);
}

t_tokens	*expand_values(t_list *args)
{
	t_tokens	*splitted;
	t_tokens	*aux;
	t_tokens	*tok;
	char		*str_aux;

	tok = list_to_token(args);
	aux = tok;
	splitted = NULL;
	while (aux)
	{
		str_aux = ft_strtrim(aux->content, " 	");
		while (!aux->content || ft_strlen(str_aux) < 1)
		{
			free(str_aux);
			aux = aux->next;
			str_aux = ft_strtrim(aux->content, " 	");
		}
		quote_split(str_aux, &splitted);
		parse_phrase(&splitted);
		aux->flag = splitted->flag;
		aux->content = join_phrases(splitted);
		//(free_lists(&splitted), splitted = NULL); // TODO: funcion de free tokens
		splitted = NULL;
		aux = aux->next;
	}
	return (tok);
}
