/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:36:00 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/15 17:53:46 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	quote_split(char *str, t_tokens **splitted)
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

int	ft_tokens_size(t_tokens *tokens)
{
	t_tokens	*aux;
	int			n;

	n = 0;
	aux = tokens;
	while (aux)
	{
		n++;
		aux = aux->next;
	}
	return (n);
}

int	*parse_phrase(t_tokens **list, int *flags, int i)
{
	t_tokens	*aux;
	char		*str_aux;

	aux = *list;
	while (aux)
	{
		str_aux = aux->content;
		if (ft_strchr(str_aux, '\'') || ft_strchr(str_aux, '"'))
			flags[i] = 1;
		else
			flags[i] = 0;
		aux->content = split_quotes(aux->content);
		free(str_aux);
		aux = aux->next;
	}
	return (flags);
}

char	*join_phrases(t_tokens *list)
{
	char		*str;
	char		*aux;
	char		*trim;
	t_tokens	*temp;

	str = ft_strdup(list->content);
	temp = list;
	while (temp->next)
	{
		temp = temp->next;
		aux = str;
		trim = ft_strtrim(temp->content, " 	");
		if (temp->content && trim != NULL)
			str = ft_strjoin(str, temp->content);
		free(trim);
		free(aux);
	}
	return (str);
}

t_tokens	*expand_values(t_list *args)
{
	t_tokens	*splitted;
	t_tokens	*aux;
	t_tokens	*tok;
	t_vars		v;

	tok = list_to_token(args);
	aux = tok;
	splitted = NULL;
	v.i = 0;
	aux = help_parsing(v, aux, splitted);
	free_lists(&args);
	return (tok);
}
