/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:36:00 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/14 13:11:30 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: Finish function for all use cases
static void	quote_split(char *str, t_list **splitted)
{
	char			len;
	int				i;
	enum e_quotes	flag;
	enum e_quotes	old_flag;

	i = 0;
	flag = 0;
	old_flag = check_flag(str, i, flag);
	while (str[i])
	{
		len = 0;
		flag = check_flag(str, i + len, flag);
		while (flag == old_flag && str[i + len])
			flag = check_flag(str, i + ++len, flag);
		if (!*splitted)
			*splitted = ft_lstnew(ft_substr(str, i, len + 1));
		else
			ft_lstadd_back(splitted, ft_lstnew(ft_substr(str, i, len + 1)));
		i = i + len + 1;
		old_flag = flag;
	}
}

static void	parse_phrase(t_list **list, char **env)
{
	t_list			*aux;
	enum e_quotes	flag;

	aux = *list;
	while (aux)
	{
		flag = check_flag(aux->content, 0, NONE);
		aux->content = remove_quotes(aux->content);
		if (flag != SINGLE)
			expand_vars(aux->content, env);
		aux = aux->next;
	}
}

static char	*join_phrases(t_list	*list)
{
	char	*str;
	char	*aux;
	t_list	*list_aux;

	list_aux = list;
	while ()
	{
		
	}
	
	return (str);
}

// TODO: 1. quote_split 2. parse_phrase -> remove quotes -> expand $ 3. join_phrases
char	**expand_values(char **args, char **env)
{
	char	**aux;
	t_list	*splitted;

	aux = args;
	splitted = NULL;
	(void)env;
	while (*aux)
	{
		quote_split(ft_strtrim(*aux, " 	"), &splitted);
		parse_phrase(&splitted, env);
		//*aux = join_phrases(splitted);
		while (splitted)
		{
			printf("splitted: %s\n", splitted->content);
			splitted = splitted->next;
		}
		(free_stacks(&splitted), splitted = NULL);
		aux++;
	}
	return (args);
}

