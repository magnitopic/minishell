/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tokens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:50:58 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/07 16:07:06 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_tokenadd_back(t_tokens **lst, t_tokens *new)
{
	if (*lst == 0)
		*lst = new;
	else
	{
		while ((*lst)->next != 0)
			lst = &(*lst)->next;
		(*lst)->next = new;
	}
}

t_tokens	*ft_token_new(char *str, int flag)
{
	t_tokens	*node;

	node = malloc(sizeof(t_tokens));
	if (!node)
		return (NULL);
	node->content = str;
	node->flag = flag;
	node->next = NULL;
	return (node);
}

void	ft_addnew_token(t_tokens **tokens, t_tokens *token)
{
	t_tokens	*new_node;

	new_node = token;
	if (!*tokens)
		*tokens = new_node;
	else
		ft_tokenadd_back(tokens, new_node);
}

void	ft_lstadd_token(t_tokens **token, char *str)
{
	t_tokens	*new_node;

	new_node = ft_token_new(str, 0);
	if (!*token)
		*token = new_node;
	else
		ft_tokenadd_back(token, new_node);
}

t_tokens	*list_to_token(t_list *lst)
{
	t_tokens	*tok;
	t_list		*aux;

	tok = NULL;
	aux = lst;
	while (aux)
	{
		ft_lstadd_token(&tok, aux->content);
		aux = aux->next;
	}
	return (tok);
}
