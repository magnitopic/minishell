/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arrays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:37:06 by jsarabia          #+#    #+#             */
/*   Updated: 2023/06/01 13:41:44 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**create_arrays(char **comms, char *name)
{
	char	**new;

	new = ft_split(comms[0], ' ');
	if (!new)
	{
		new = ft_calloc(2, sizeof(char *));
		new[0] = ft_substr(name, 0, ft_strlen(name));
		return (new);
	}
	return (new);
}
