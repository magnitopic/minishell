/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:36:00 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/13 20:01:30 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	quote_split(char *str, t_list *splitted)
{
	char	len;
	int		i;

	i = 0;
	(void)splitted;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			len = 0;
			while ((str[len] != '\'' && str[len] != '"') && str[i])
			{
				len++;
				printf("%d\n", len);
			}
			printf("test: %s\n", ft_substr(str, len, ft_strlen(str) - len));
		}
		i++;
	}
}

/* static void	parse_phrase(t_list *list)
{
	while (**list)
	{
		
		list = list->next;
	}
	
} */

char	**expand_values(char **args, char **env)
{
	char	**aux;
	t_list	*splitted;

	aux = args;
	splitted = NULL;
	(void)env;
	while (*aux)
	{
		quote_split(*aux, splitted);
		/* parse_phrase(&splitted);
		*aux = join_phrases(splitted); */
		aux++;
	}
	return (args);
}

