/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:36:00 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/02 18:59:53 by jsarabia         ###   ########.fr       */
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

static void	parse_phrase(t_list **list)
{
	t_list	*aux;
	char	*str_aux;

	aux = *list;
	while (aux)
	{
		str_aux = aux->content;
		aux->content = split_quotes(aux->content);
		free(str_aux);
		aux = aux->next;
	}
}

static char	*join_phrases(t_list *list)
{
	char	*str;
	char	*aux;

	//str = ft_strtrim(list->content, " 	");
	str = list->content;
	while (list->next)
	{
		list = list->next;
		aux = str;
		if (list->content && ft_strtrim(list->content, " 	") != NULL)
			//str = ft_strjoin(str, ft_strtrim(list->content, " 	"));    // ! Si hay segfault, seguramente sea porque hemos cambiado esto recientemente
			str = ft_strjoin(str, list->content);
		free(aux);
	}
	return (str);
}

void	ft_lstadd_token(t_tokens **token, char *str)
{
	t_tokens	*new_node;

	new_node = (t_tokens *)(ft_lstnew(str));
	if (!*token)
		*token = new_node;
	else
		ft_lstadd_back((t_list **)token, (t_list *)new_node);
}

t_tokens	*list_to_token(t_list *lst)
{
	t_tokens	*tok;

	tok = NULL;
	while (lst)
	{
		ft_lstadd_token(&tok, lst->content);
		lst = lst->next;
	}
	return (tok);
}

t_tokens	*expand_values(t_list *old_args)
{
	t_list		*splitted;
	t_tokens	*aux;
	t_tokens	*args;
	char		*str_aux;

	args = list_to_token(old_args);
	ft_printf("size: %d\n", ft_lstsize((t_list *)args));
	aux = args;
	while ((t_list *)args)
	{
		ft_printf("jamon\n"); // ! Esto peta y hay que cambiarlo
		args = args->next;
	}
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
		parse_phrase(&splitted);
		args->content = join_phrases(splitted);
		(free_lists(&splitted), splitted = NULL);
		ft_printf("%s\n", args->content);
		if (args->next)
			args = args->next;
	}
	return (aux);
}
