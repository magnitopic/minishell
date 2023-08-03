/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tokens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:50:58 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/03 12:02:58 by alaparic         ###   ########.fr       */
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

static t_tokens	*ft_token_new(char *str)
{
	t_tokens	*node;

	node = malloc(sizeof(t_tokens));
	if (!node)
		return (NULL);
	node->content = str;
	node->flag = 0;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_token(t_tokens **token, char *str)
{
	t_tokens	*new_node;

	new_node = ft_token_new(str);
	if (!*token)
		*token = new_node;
	else
		ft_tokenadd_back(token, new_node);
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