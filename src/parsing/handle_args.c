/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:36:00 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/14 09:31:43 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	quote_split(char *str, t_list *splitted)
{
	char			len;
	int				i;
	enum e_quotes	flag;

	i = 0;
	flag = NONE;
	(void)splitted;
	while (str[i])
	{
		len = 0;
		printf("flag: %d\n", check_flag(str, i + len, flag));
		while (check_flag(str, i + len, flag) != 0)
		{
			printf("%c\n", str[i + len]);
			len++;
		}
		printf("test: %s\n", ft_substr(str, len, ft_strlen(str) - len));
		printf("str: %s\n", ft_substr(str, 0, i));
		i += len;
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
		printf("----------------\n");
		/* parse_phrase(&splitted);
		*aux = join_phrases(splitted); */
		aux++;
	}
	return (args);
}

