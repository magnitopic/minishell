/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:23:27 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/15 17:53:57 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tokens	*help_parsing(t_vars v, t_tokens *aux, t_tokens *splitted)
{
	v.flags = ft_calloc(ft_tokens_size(aux), sizeof(int));
	v.i = 0;
	while (aux)
	{
		v.aux = ft_strtrim(aux->content, " 	");
		while (!aux->content || ft_strlen(v.aux) < 1)
		{
			free(v.aux);
			aux = aux->next;
			v.aux = ft_strtrim(aux->content, " 	");
		}
		quote_split(v.aux, &splitted);
		v.flags = parse_phrase(&splitted, v.flags, v.i);
		aux->flag = v.flags[v.i];
		aux->content = join_phrases(splitted);
		free_tokens(&splitted);
		aux = aux->next;
		v.i++;
	}
	free(v.flags);
	return (aux);
}
