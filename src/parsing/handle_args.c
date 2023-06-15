/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:36:00 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/15 14:58:14 by jsarabia         ###   ########.fr       */
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
	t_list			*new_element;

	i = 0;
	flag = 0;
	old_flag = check_flag(str, i, flag);
	while (str[i])
	{
		len = 0;
		flag = check_flag(str, i + len, flag);
		while (flag == old_flag && str[i + len])
			flag = check_flag(str, i + ++len, flag);
		if (old_flag != NONE)
		{
			new_element = ft_lstnew(ft_substr(str, i, len + 1));
			i = i + len + 1;
		}
		else
		{
			new_element = ft_lstnew(ft_substr(str, i, len));
			i = i + len + 1;
		}
		if (!*splitted)
			*splitted = new_element;
		else
			ft_lstadd_back(splitted, new_element);
		printf("Splitted: %s\n", new_element->content);
		old_flag = flag;
	}
}

static void	parse_phrase(t_list **list, char **env)
{
	t_list			*aux;
	//enum e_quotes	flag;

	aux = *list;
	while (aux)
	{
		aux->content = split_quotes(aux->content, env);
		printf("spliteao: %s\n", aux->content);
		aux = aux->next;
	}
}

static char	*join_phrases(t_list	*list)
{
	char	*str;
	char	*aux;

	str = "";
	while (list)
	{
		aux =  ft_substr(str, 0, ft_strlen(str));
		if (ft_strlen(str) > 0)
			free(str);
		str = ft_strjoin(str, list->content);
		free(aux);
		list = list->next;
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
		*aux = join_phrases(splitted);
		printf("Aux: %s\n", *aux);
		(free_stacks(&splitted), splitted = NULL);
		aux++;
	}
	return (args);
}

