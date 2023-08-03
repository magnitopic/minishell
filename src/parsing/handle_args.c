/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:36:00 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/03 15:10:00 by jsarabia         ###   ########.fr       */
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

static t_tokens	*parse_phrase(t_list *list)
{
	char		*str_aux;
	t_list		*aux;
	t_tokens	*tokens;

	aux = list;
	while (aux)
	{
		str_aux = aux->content;
		ft_lstadd_tokens(&tokens, split_quotes(aux->content));
		free(str_aux);
		aux = aux->next;
	}
	return (tokens);
}

static t_tokens	*join_phrases(t_list *list)
{
	char		*str;
	char		*aux;
	t_tokens	*tok;

	//str = ft_strtrim(list->content, " 	");
	str = list->content;
	while (list->next)
	{
		list = list->next;
		aux = str;
		if (list->content && ft_strtrim(list->content, " 	") != NULL)
			//str = ft_strjoin(str, ft_strtrim(list->content, " 	"));	// ! Si hay segfault, seguramente sea porque hemos cambiado esto recientemente
			str = ft_strjoin(str, list->content);
		free(aux);
	}
	return (str);
}

t_tokens	*expand_values(t_list *old_args)
{
	t_list		*splitted;
	t_tokens	*aux;
	t_tokens	*args;
	char		*str_aux;

	args = list_to_token(old_args);
	aux = args;
	splitted = NULL;
	while (args)
	{
		str_aux = ft_strtrim(args->content, " 	");
		while (!args->content || ft_strlen(str_aux) < 1)
		{
			free(str_aux);
			args = args->next;
			str_aux = ft_strtrim(args->content, " 	");
		}
		quote_split(str_aux, &splitted);
		args = parse_phrase(splitted);
		ft_printf("ey: %s\n", args->content); // TODO: remove
		args = join_phrases(args); // TODO: Modify so that redirects are not joined
		(free_lists(&splitted), splitted = NULL);
		args = args->next;
	}
	return (aux);
}
