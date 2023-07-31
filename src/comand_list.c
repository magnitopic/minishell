/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:35:51 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/31 19:47:42 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_add_back_command(t_redi **lst, t_redi *new)
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

static t_redi	*ft_lstnew_command(void *content, enum e_redirect type)
{
	t_redi	*node;

	node = malloc(sizeof(t_redi));
	if (!node)
		return (NULL);
	node->content = content;
	node->type = type;
	node->next = NULL;
	return (node);
}

void	ft_newcommand(t_redi **list, void *cont, enum e_redirect type)
{
	t_redi	*new_redirect;

	new_redirect = ft_lstnew_command(cont, type);
	if (!*list)
		*list = new_redirect;
	else
		ft_add_back_command(list, new_redirect);
}

void	ft_new_arg()    // TODO: hay que hacer esta función <3
